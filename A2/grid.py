#Written in OO
#The grid (and possibly its contents) must be prepresented as an object
#Contain code for grid content & any game/scoring data. 
import random

class Cell:
    def __init__(self, value):
        self.value = value
        self.isRevealed = False
    
    def reveal(self):
        self.isRevealed = True

    def hide(self):
        self.isRevealed = False
    
    def __str__(self):
        return str(self.value) if self.isRevealed else "X"

class Grid:
    def __init__(self, size):
        self.size = size
        self.cells = self.createGrid()
    
    def createGrid(self):
        numberOfPairs = ((self.size**2) //2)
        values = [i for i in range(0, numberOfPairs)] * 2
        random.shuffle(values)

        return [[Cell(values.pop()) for _ in range(self.size)] for _ in range(self.size)]
    
    def displayGrid(self):
        for row in self.cells:
            print("     "+"    ".join(str(cell) for cell in row))
        print()


