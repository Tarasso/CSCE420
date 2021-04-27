# Proj5

My project can be compiled using `make` and ran using `./resolution <*.cnf> <query> <optional: -n flag denoting negated query>`
  - The first two arguments (the .cnf file and query) are required
  - Note that the following `-n` flag is added when running the resolution on a negated query such as `"(not Q)"`

Resolution takes a given .cnf file, adds the negated query, verifies and parses the given rules, and displays the KB before starting the resolution algorithm 

The CNF file for the wumpus world problem can be generated using the python script `wumpusGen.py`

Example output transcripts can be found in the `transcripts` directory