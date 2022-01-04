describe 'database' do
  def run_script(commands)
    raw_output = nil
    IO.popen("./REPL teste.db", "r+") do |pipe|
      commands.each do |command|
        pipe.puts command
      end

      pipe.close_write

      raw_output = pipe.gets(nil)
    end
    raw_output.split("\n")
  end

  it 'inserts and retrieves a row' do
    result = run_script([
      "insert 1 user1 person1@example.com",
      "select",
      ".exit",
    ])
    expect(result).to match_array([
      "db> Executed ",
      "db> (1, user1, person1@example.com)",
      "Executed ",
      "db> ",
    ])
  end

  it 'keeps data after closing connection' do
    result_1 = run_script([
      ".exit"
    ])

    result_2 = run_script([
      "select",
      ".exit"
    ])
    expect(result_2).to match_array([
      "db> (1, user1, person1@example.com)", 
      "Executed ", 
      "db> " 
    ])
  end

  #it 'tests TABLE_MAX_ROWS' do
  #  script = (1..1401).map do |i|
  #    "insert #{i} person#{i} person#{i}@gmail.com"
  #  end
  #  script << ".exit"
  #  result = run_script(script)
  #  expect(result[-2]).to eq("db> Error: Table full. ")
  #end

  it 'allows inserting strings that are the maximum length' do
    long_username = "a"*33
    long_email = "a"*256
    script = [
      "insert 14 #{long_username} #{long_email}",
      ".exit",
    ]
    result = run_script(script)
    expect(result).to match_array([
      "db> String is too long",
      "db> ",
    ])
  end

  it 'You cant not submit a negative id' do
    script = [
      "insert -1 person1 person1@gmail.com", 
      ".exit"
    ] 
    result = run_script(script)
    expect(result).to match_array([
      "db> This id is negative ", 
      "db> "
    ])
  end

  it 'prints constants' do 
    script = [
      ".constants", 
      ".exit",
    ]
    result = run_script(script);
    expect(result).to match_array([
      "db> Constants: ",
      "ROW_SIZE: 293", 
      "COMMON_NODE_HEADER_SIZE: 6",
      "LEAF_NODE_CELL_SIZE: 297",
      "LEAF_NODE_SPACE_FOR_CELLS: 4086",
      "LEAF_NODE_HEADER_SIZE: 10",
      "LEAF_NODE_MAX_CELLS: 13",
      "db> ",
    ])
  end 


end