# A simple file-data ascii-hex translator.

This is mainly a learning project, but still relatively useful

compile with 
```bash
$ make
```

or

```bash
$ g++ -o stx.exe main.cpp
```

Use:
	
```bash
$ stx [-x] filename
$ stx [-s] filename
```
	-x : translates file data to its hexadecimal equivalent
	-s : translates file data from hex to ascii characters.
