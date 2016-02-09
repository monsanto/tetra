/*
 TETRAGUESS
 ----------------
 Written by Chris Monsanto.
 ----------------
 
 The first complete program written in Tetra.
 Ph33r.
*/

print("TETRAGUESS.T by Chris Monsanto\n") ;

infinity {
 range1 = input("Lowest number:") ;
 range2 = input("Highest number:") ;
 $guesses = input("How many guesses?") ;
 $real_number = rand(range1,range2) ;
 game() ;
 print("It took you " . $amount_guesses . " try(s)\n\n") ;
 answer = input("Press Enter to play, N to quit.") ;
 if (answer == "N")
  return ;
 $amount_guesses = 0 ;
 $guesses = 0 ;
}

function game {
 while ($amount_guesses < $guesses) {
  $amount_guesses = $amount_guesses + 1 ;
  guessed_number = input("Number?") ;
  if (guessed_number < $real_number)
   print("Too low!\n") ;
  else if (guessed_number > $real_number)
   print("Too high!\n") ;
  else {
   print("Correct!\n") ;
   return ;
  }
 }
 print("Too bad! The number was " . $real_number . "\n") ;
}