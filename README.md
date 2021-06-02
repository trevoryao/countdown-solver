# countdown-solver
Simple, efficient, & multithreaded solver for the countdown numbers game.

## Instructions
```
countdown-solver [options] -t <target> -n <5 numbers>
countdown-solver [options] -n <5 numbers> (CECIL will generate target)
countdown-solver [options] -t <target> -b <# of big'uns> -l <# of little ones>
countdown-solver [options] -b <# of big'uns> -l <# of little ones> (CECIL will generate)

Options:
  -h [ --help ]         Help Screen
  -j [ --json ]         print in json format
  -o [ --out ] arg      output to file
  -t [ --target ] arg   Target
  -n [ --numbers ] arg  5 numbers
  -b [ --biguns ] arg   # of biguns (must be 5 - littluns)
  -l [ --littluns ] arg # of littluns (must be 5 - biguns)
```
