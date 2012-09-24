CSE274 Fall 2012
HW-2 The Royal Society for Putting Things on Top of Other Things

Main Goals(70 pts):
A. Linked-List type data structure - Both Circle and Color Cards are organized as circular doubly linked never empty lists.(30)
B. Help Message - A help message is displayed on start up and whenever the user inputs '?'(10)
C. Re-Order - The deck is cycled when the user hits 'n' (10)
E. Reversal - The Color Cards can be reordered by hitting the 'r' button (10)
G. Transparency - The light pegs glow with transparency(10)
H. Depth - The Color Cards are stacked like a deck which indicates the depth of the cards in the stack(10)

//I realize that this is 80 out of 70 points possible, so if one item does not meet the specification, just use another one.

Stretch Goals(10):
J. Make a Game - I made a Lite Brite.


NOTES:
I know the video I posed prior to the final version had more light placement animation, but this caused issues with loss of frame rate which is needed for the lights to blink and shuffling the cards quickly after the board was filled with 20+ lights. This was resolved by combining the lights and the pegs into a single object and removing the animation. 