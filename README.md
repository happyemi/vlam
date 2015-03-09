### Overview
LVAM stands for "Very Large Array of Monkeys". It's a library that can be used to generate sensible random text, in the same way as monkeys would do (provided they can hit the keyboard for enough time...). It has NOT any claim to be a formal grammar, it's just a tool can be useful if you want to add some randomness to your text.

LVAM is supposed to be a library, but it also comes with a command line tool, called vlam_parse that can be used to have some fun from the command line. It reads text from the standard input until EOF is reached, and writes its output on the standard output.

### Manual
(WIP, I'm adding things here as soon as I implement them)

1. English characters and some ASCII symbols are just copied to the output stream. So the simpler input text you can have is "Hello world!", which gets copied as is to the output stream

2. Curly brackets are used to implement _Random Lists_ i.e. a list of elements separated by a `|`. Only one element will be selected by the parser and copied to the output.
Example: `The {first|second} world` can result in:

  1. `The first world` or

  2. `The second world`

Random Lists can't be nested (for now)

### Building
Building the commandline program requires flexc++ and bisonc++ installed. Building tests requires libboost-test.

1. `scons vlam_parse` or just `scons` builds the main command line executable. Run with `src/vlam_parse`. It reads data from the standard input.

2. `scons test` builds the unit tests. Run with `test/vlam-test`

