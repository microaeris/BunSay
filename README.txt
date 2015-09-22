     ____
 ___(__  \
(__  \ \  |
   \__\|__|
  /  _    _\
 /   _    _ |
 \..[_] .[_]|
  \`____^__/
   /|x-x-|\
  / |-x-x| \
 '-'/x-x-\`-'
   /______\
    | | | |
    \_\ \_\
╔╗ ┬ ┬┌┐┌╔═╗┌─┐┬ ┬
╠╩╗│ ││││╚═╗├─┤└┬┘
╚═╝└─┘┘└┘╚═╝┴ ┴ ┴

CARE INSTRUCTIONS

  Thank you for adopting Ruby in this command line villager simulator! She is a peppy bunny from Animal Crossing New Leaf. Get to know her more by running the program. You will learn about her favorite coffee, catchphrase, career and more. She will also say any quotes you pass to her. 

  You can dress her up and choose different poses! Try them all out.

  -a    Bunny in Ayy dress

  -b    Bunny bling

  -c    Bunny with cane

  -d    Bunny in a polka dot dress

  -g    Grumpy bunny

  -i    Bunny in a striped dress

  -m    Bunny in a smilie dress

  -r    Bunny in the Ruby dress

  -s    Bunny in a star dress

  -t    Bunny in a top and skirt

  You can also give her gifts with --give <gift>

AUTHOR

  Alice Wang, July 21, 2015
  This program is inspired by cowsay and Animal Crossing.

  For more things at the intersection of CS and cute: 
  https://github.com/Ahris/

INSTALL

  Use your favorite C compiler! I personally used gcc:
  gcc -o bunsay bunsay.c -std=c99

  If you run out of things for Ruby to say, you can pipe fortunes to BunSay.
  More about Fortune here: https://en.wikipedia.org/wiki/Fortune_(Unix)

BUGS + TODO

  Ignore this section - this is just a note to self. 

  ./bunsay -c -give apple seg fault
  ./bunsay -c -give apple seg faults
  Random quotes are seeded by time, not random enough. 
  Refactoring labeled stuff.
  quote with no spaces will break the bubble


  Done
  strings that are 32 characters long break the bubble (extra space at end)