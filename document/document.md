### Chess Game Project

## Introduction

In this project, our task is to implement a chess game in C++. </br>
Chess is basically a two-player board game where the board is 8 x 8 with a black and white checkered pattern. </br>
Each side has a total of 16 pieces(1 King, 1 Queen, 2 Rooks, 2 Bishops, 2 Knights and 8 Pawns).</br>
Different type of pieces have different available moves, and it can capture the opponent’s piece by moving to the piece’s position.</br>
The game can end by either a checkmate, stalemate, or resignation. 
Checkmate happens when one of the players is threatening the other player's king, and it cannot move to any other squares, 
cannot be protected by another piece and the checking piece cannot be captured. </br>
If all of these conditions are met, the attacking player wins via checkmate. 
A stalemate is when the player to move has no legal moves but is not in check, it is therefore a draw. If a player chooses to resign, then the opposing player wins.</br>
</br>

## UML

![uml](https://user-images.githubusercontent.com/70479629/210186831-fa7318ec-01ba-4a34-966b-79a576f4f2e2.png) </br>
</br>

## Overview
The project is a implementation of the game of chess. It includes classes for representing the chess board, individual pieces, moves, and the overall game. 
The project also includes classes for implementing computer players at different levels of difficulty, as well as classes for displaying the game using a command line interface or a graphical user interface.</br>
</br>

The main class for the chess game is the Chess class, which maintains the state of the game and provides methods for making moves, 
checking for check or checkmate, and undoing moves. 
The Chess class also maintains a Scoreboard object, which tracks the score and any special moves (such as castling or en passant) made during the game.</br>
</br>

The Pieces class is an abstract base class that defines the common behavior and attributes of all chess pieces. 
It includes methods for checking if a move is valid, as well as for checking for special moves such as castling or en passant. 
Each specific type of piece (e.g. King, Queen, Rook, etc.) is represented by a subclass of Pieces, which overrides the methods as necessary 
to implement the unique rules and behavior of that piece.</br>
</br>

The Move class represents a single move made in the game, and includes information about the original and new positions of the piece, 
any piece that was captured, and any promotion that occurred. 
The class also maintains a string to track any special status or comments associated with the move.</br>
</br>

The Controller class provides a high-level interface for playing a game of chess, including methods for moving pieces, checking the game state, 
undoing moves, and handling pawn promotions. 
The Controller also has references to Computer objects, which can be used to play against the computer at different levels of difficulty.</br>
</br>

The Observer classes, Cli and Gui, provide interfaces for displaying the game state and receiving notifications of changes. 
The Cli class implements a command line interface, while the Gui class uses the XWindow library to draw the game board and pieces using graphical elements.</br>
</br>

The Computer class is an abstract base class that defines the common behavior and attributes of computer players. 
It includes methods for selecting a move, as well as for adjusting the difficulty level. 
The specific levels of difficulty (e.g. Level1, Level2, etc.) are represented by subclasses of Computer, which override the methods as necessary to implement the desired level of AI.</br>
</br>

Our ‘Board’ class simply represents the 8 × 8 chess board by using a 2D array of characters.</br>

The project save the score of all games in the ‘ScoreBoard’ class.</br>

The enumeration class ‘Position’ keeps track of all the pieces position on the board.</br>
</br>

## Design
The project involved several design challenges, which were addressed using various techniques.</br>
</br>

One of the main challenges was to implement the different types of chess pieces, each with its own unique set of rules for movement and capture.</br>
To solve this challenge, we used the object-oriented programming technique of creating separate classes for each type of piece,
with each class containing the specific logic for that piece's movement and capture rules. 
We also used inheritance to allow the pieces to share common attributes and methods, such as the ability to identify the piece's color and position on the board.</br>
</br>

Another challenge was to implement the board and its cells, which needed to be able to store and manage the various pieces on the board.</br>
To solve this challenge, We used the concept of a two-dimensional array to represent the board, with each cell of the array storing 
a pointer to the piece occupying that cell on the board. 
We also used the observer design pattern to enable the board to notify other classes, such as the GUI and CLI, when the state of the board has changed, 
such as when a piece is moved or captured.</br>
</br>

Another challenge was to implement the different game modes, including the ability to play against the computer with different levels of difficulty.
To solve this challenge, We used the strategy design pattern to allow the game to easily switch between different modes, such as human vs. human, 
human vs. computer, and computer vs. computer. We also implemented different computer player classes, each with its own algorithm for determining its next move, 
allowing the game to adjust the level of difficulty by using different player classes.</br>
</br>

Overall, the project employed various techniques from object-oriented programming, design patterns, and data structures to solve the various design 
challenges and provide a functional and extensible chess game.</br>
</br>
</br>

## Resilience to Change
Our project is resilient to change because it is designed using the MVC model and observer pattern. This allows for a clear separation of concerns, 
with the 'Chess' class managing the logic and data of the game, the 'Observer' class and its subclasses handling the display of the game, 
and the 'Controller' class managing interactions and modifying data. This modular design makes it easy to change or add new features without 
impacting the overall structure of the project. For example, if we wanted to add a new level of computer play, we could simply create a new subclass 
of the 'Computer' class without modifying the existing code. Similarly, if we wanted to change the way the game is displayed, 
we could modify the 'Observer' class or create a new subclass without affecting the logic of the game. This design makes the project resilient 
to change and allows for easy expansion and modification.</br>
</br>

Therefore, our project has high cohesiveness because the classes and functions are logically grouped and work together to achieve a common goal. 
For example, the 'Chess' class manages the logic and data of the game, the 'Observer' class and its subclasses handle the display of the game, 
and the 'Controller' class manages interactions and modifies data. Each class has a clear and well-defined purpose, and all the classes work 
together to implement the chess game. This high cohesiveness makes the project easy to understand and maintain.</br>
</br>

Our project also has low coupling because the classes are independent and do not depend on each other's implementation details. 
For example, the 'Chess' class does not need to know how the game is displayed or how the user interacts with it. 
It only needs to provide the necessary information and functions for the other classes to use. 
This low coupling makes the project more flexible and allows for easier modification and expansion. 
For example, if we wanted to change the way the game is displayed, we could modify the 'Observer' class or create a new subclass without affecting 
the logic of the game. This low coupling makes the project more resilient to change and allows for easier maintenance and development.</br>
</br>

## Conclusion
In conclusion, the implementation of the Chess game in C++ using the MVC model and observer pattern was successful. 
The project consisted of various virtual abstract classes and their subclasses, including the model class 'Chess', which managed application data 
and modified it as needed. The 'Observer' class was the virtual abstract class for the 'CLI' and 'GUI' classes, which handled the command line interface 
and graphical user interface, respectively. The 'Computer' virtual abstract class had four subclasses, each handling a different level of computer play. 
The 'Board' class represented the 8x8 chess board, and the 'Pieces' class was the virtual abstract class for the six classes representing each game piece. 
The 'ScoreBoard' class kept track of game scores, and the 'Position' enumeration class kept track of the positions of all pieces on the board. 
The 'Controller' class managed interactions and modified data by calling the 'movePiece' function in the 'Chess' class. 
The main function handled user input and controlled the flow of the game. 
Overall, this project successfully implemented a functioning chess game with the ability to support human vs computer play at different levels. 
Although we had many changes and improvements, I think we have completed the project to the best of our abilities, implementing several extra features as well.</br>