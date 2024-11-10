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
        self.minGuess = (size/2)**2
    
    def createGrid(self):
        numberOfPairs = ((self.size**2) //2)
        values = [i for i in range(0, numberOfPairs)] * 2
        random.shuffle(values)

        return [[Cell(values.pop()) for _ in range(self.size)] for _ in range(self.size)]
    
    def displayGrid(self):
        column_labels = "     " + "  ".join(f"[{chr(65 + i)}]" for i in range(self.size))
        print(column_labels)
        i = 0
        for row in self.cells:
            print("["+str(i)+"]".strip()+"   "+"    ".join(str(cell) for cell in row))
            i += 1
        print()
    
    def revealCell(self,column,row):
        cell = self.cells[row][column]
        cell.reveal()
        return cell.value
    
    def hideCell(self, column, row):
        cell = self.cells[row][column]
        cell.hide()
        
    def revealAll(self):
        for i in range(self.size):
            for j in range(self.size):
                self.cells[i][j].reveal()
    
    def newGrid(self):
        for i in range(self.size):
            for j in range(self.size):
                self.cells[i][j].hide()
        self.cells = self.createGrid()

    def isWon(self):
        for row in self.cells:
            for cell in row:
                if not cell.isRevealed:
                    return False
        return True

    def calculateScore(self, guess):
        if guess == 0:
            return 0
        return (self.minGuess/guess)*100
    




