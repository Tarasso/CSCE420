# Proj4

My project can be compiled using `make` and ran using `./dpll <cnf file> <optional: -unit flag>`

The ./dpll takes a given .cnf file, extracts the symbols, parses the rules, and displays the KB before starting the DPLL algorithm 

CNF files can be generated using the python scripts
  - `mapKBgen.py`
  - `queensKBgen.py`
    - Open the file and change the `queens` variable to support any size queen problem

Example output transcripts can be found in the repo with the names `DPLL_*.txt`

The `RESULTS.txt` file contains a summary of all above tests ran

Additionally, I provided a solution to the 15 queens problem! :)