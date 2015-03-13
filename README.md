### Overview
VLAM stands for "Very Large Array of Monkeys". It's a library that can be used to generate sensible random text, in the same way as monkeys would do (provided they can hit the keyboard for enough time...). It has NOT any claim to be a formal grammar, it's just a tool can be useful if you want to add some randomness to your text.

VLAM is supposed to be a library, but it also comes with a command line tool, called `vlam_parse` that can be used to have some fun from the command line. It reads text from the standard input until EOF is reached, and writes to the standard output.

### Manual (sort of)

1. The syntax of the input file is:
  ```
  $variable_name_1 = <TEXT>
  ...

  <TEXT>
  ```

  Variable definitions are optional, so only `<TEXT>` is mandatory to have a valid input. `TEXT` can be any combination of characters; they pretty much get copied to the output, with the exception of the special characters needed for VLAM to make its job.

2. Curly brackets are used to implement _Random Lists_ i.e. a list of elements separated by a `|`. Only one element will be selected by the parser and copied to the output. Example: 

  `The {first|second} world` can result in:

  1. `The first world` or

  2. `The second world`

 _Random Lists_ can be nested. For example, the following text:

 `Hello {first|my {second|third} lovely} world`can result in:

  1. `Hello first world` or

  2. `Hello my second lovely world` or
  
  3. `Hello my third lovely world`

  Please note that these three alternative do NOT have the same chance to be selected. `{second|third}` have both a 50% chance to be selected. The parent _Random List_ will then select either branch with 50% chance each. This means that `Hello first world` has 50% probability to be generated, while `Hello my second lovely world` and `Hello my third lovely world` have 25% probability each to be generated.

3. Square brackets are used to generate _Optional Text_. The text between a pair of brackets has a 50% chance to be generated. For example:

  `Hello[ world]`

  can result in:

  1. `Hello world` or
  
  2. `Hello`

4. _Optional Text_ and _Random Lists_ can be nested without problems. All the following possibilites are valid:
  
  * `Hello {[my ]first|second} world`. It can generate:
    
     1. `Hello first world` or
	
     2. `Hello my first world` or
	
     3. `Hello second world`

     Note that #3 has 50% chance to be generated. #1 and #2 have 25% chance each.

  * `Hello [{first|second}] world`. It can generate:

     1. `Hello world` or

     2. `Hello first world` or

     3. `Hello second world`

     Note that #1 has 50% chance to to be generated. #2 and #3 have 25% chance each.
  
 There is no limit to nesting, but the probability of the generation of the text will lower with each nesting level.

5. _Variables_ are identifiers that store text and that, when used, are replaced by their content. Only _Variables_ that have been previously defined can be used. Example:
  ```
  $myVar = <This is a variable>
  <Variable text: $myVar>
  ```

  The previous text will generete: `Variable text: This is a variable`

  Note that all _Optional Text_ and _Random Lists_ that appear in a variable definition are only generated once and their value is reused every time the variable is referred

6. Parsing error reporting is _very_ limited: `Vlam::parse` will throw an exception when a syntax error is detected, but will only report the offending line number. Good luck finding that pair of unmatched parenthesis...

### Building
Building the commandline program requires flexc++ and bisonc++ installed. Building tests requires libboost-test.

1. `scons vlam_parse` or just `scons` builds the main command line executable. Run with `src/vlam_parse`. It reads data from the standard input.

2. `scons test` builds the unit tests. Run with `test/vlam-test`

3. `scons install` will copy the library files into the `install` directory, located in the source root.

