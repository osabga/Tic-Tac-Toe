# Tic Tac Toe with AI Opponent in C++ 

This project involves creating a Tic Tac Toe game in C++ where the second player can be a bot. The bot uses minimax algorithm and memoization to make its moves always aiming to make a perfect game (winning or tying).

The project was completed in collaboration by [@osabga](https://www.github.com/osabga) and [@samsbg](https://www.github.com/samsbg). The main responsibilities for [@osabga](https://www.github.com/osabga) were implementing the minimax algorithm, user interface, and input handling, while [@samsbg](https://www.github.com/samsbg) was responsible for the general structure and making the minimax algorithm more efficient.

## Fun facts

-	For the memoization, the way to save the state of the game was through converting the grid into a base 3 number depending on the symbol in it, then use that number in a dictionary to save the minimax score

![image](https://user-images.githubusercontent.com/70488844/210968616-f6f18cc3-80b1-4e08-9e1c-5e3fb3095404.png)

-Our code uses a really cool feautre of arrays, in c++ arrays dont need to be return to be modify by a function, this is due to the nature of the data structure. Arrays work with pointers, so when we pass a array to a function, we actually are sentind a pointer to the head of the array, this means all modifications made will remain making the code cleaner, due to the fact that we are not returning anything. 

## License

[MIT](https://choosealicense.com/licenses/mit/)

