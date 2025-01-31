import java.util.Scanner;

public class ConnectFour
{
	public static void main (String[] args)
	{	
		boolean playAgain=true;
		
		while(playAgain) 
		{
			Scanner input;
			char[][] board = new char[6][7];
			int noOfDisk = 0;
			char color;
			String player=" ";
		    int disk;
		    fillBoard(board);
		    int column=0;
		    
			while (isWinner(board) == false && noOfDisk != 6 * 7) 
			{	
				printBoard(board);
								
				boolean incorrectInput=true;
			    while(incorrectInput) {
			    	input = new Scanner(System.in);
			    	column = input.nextInt();
			    	
			    	for(int i=0;i<7;i++) 
			    	{
			    		if(column==i) 
			    		{
			    			incorrectInput=false;
			    			break;
			    		}
				    }
			    	if(incorrectInput) 
			    	{
			    		System.out.println("Invalid input.Please enter a column number (0-6)");
			    	}
			    }
				
				if ( noOfDisk % 2 == 0)
				{
					color = 'Y';
					player = "Yellow";
				}
				else 
				{
					color = 'R';
					player = "Red";
				}
				noOfDisk++;
				
				System.out.print("");				
			   	
				dropDisk(board,column,color);		
			}
			
		    if(isWinner(board)) 
		    {
		     System.out.println("The " + player + " player won");	      
		    }
		    else 
		    {
		     System.out.println("It is a draw.");
		    }
		    
		    System.out.println( "DO YOU WANT TO PLAY A NEW GAME? (type 1 for yes)");
		    
		    Scanner decision = new Scanner(System.in);
		    
		    boolean incorrectInput=true;
		    while(incorrectInput) {
			    if(decision.nextInt()==1) 
			    {
			    	playAgain=true;
			    	incorrectInput=false;
			    }
			    else if(decision.nextInt()==0) 
			    {
			    	playAgain=false;
			    	incorrectInput=false;
			    }
			    else 
			    {
			    	System.out.println("Incorrect input.please try again");
			    	incorrectInput=true;		    	
			    }
		    }
		}
    }
	public static char[][] fillBoard(char[][] board)
	{
		for (int i = 0; i < board.length; i++ )
		{
			for (i=0;i<6;i++) 
			{
				for(int j=0;j<7;j++) 
				{
					board[i][j] = ' ';
				}
			}
		}
	return board;
	} 
	private static void printBoard(char[][] board)
	{
		for(int i = board.length - 1; i >= 0; i--)
		{
			System.out.print("| ");
			for(int j = 0; j <board[i].length; j++)
			{
				System.out.print(board[i][j] + " | ");
			}
			System.out.println();//new line
		}
	}
	public static void dropDisk(char[][] board, int column, char color)
	{ 
		while(columnIsFull(board,column)) 
		{
			System.out.println("The column is full. Please enter another column");
			boolean incorrectInput=true;
		    while(incorrectInput) {
		    	Scanner newColumn = new Scanner(System.in);
		    	column = newColumn.nextInt();
		    	
		    	for(int i=0;i<7;i++) 
		    	{
		    		if(column==i) 
		    		{
		    			incorrectInput=false;
		    			break;
		    		}
			    }
		    	if(incorrectInput) 
		    	{
		    		System.out.println("Invalid input.Please enter a column number (0-6)");
		    	}
		    }
		}
		for(int i=0; i<6; i++) 
		{
			if(board[i][column]==' ')
			{
				board[i][column]=color;
				return;
			}
		}
	}
	public static boolean columnIsFull(char[][] board,int col) 
	{
		for(int i=5; i>=0; i--) 
		{
			if(board[i][col]==' ')
			{
				return false;
			}
		}
		return true;
	}
	public static boolean isWinner(char[][] board)
	{	
	// checking for horizontal win
		for (int i=0; i<board.length; i++)
		{
			for(int j=0; j<board[i].length -3; j++)
			{
				if(board[i][j] !=' '
				&& board[i][j] == board[i][j+1]
				&& board[i][j] == board[i][j+2]
				&& board[i][j] == board[i][j+3])
				{
				return true;					
				}					
			}								
		}
	//	checking for vertical win
		for (int j=0; j<board[0].length; j++)
		{
			for (int i=0; i<board[0].length-3; i++)
			{
				if(board[i][j] !=' '
				    && board[i][j] == board[i+1][j]
				    && board[i][j] == board[i+2][j]
				    && board[i][j] == board[i+3][j])
				{
					return true;
				}
			}
		}
	// checking for diagonal win, from top left to bottom right
		for (int i=0; i<board.length-3; i++)
		{
			for (int j=0; j<board[i].length - 3; j++)
			{
				if(board[i][j] != ' '
					&& board[i][j] == board[i+1][j+1]
                    && board[i][j] == board[i+2][j+1]
                    && board[i][j] == board[i+3][j+3] )
				{
					return true;
				}
			}
		}
		
	// checking for diagonal win, from top right to bottom left
		for(int i=0; i<board.length-3; i++)
		{
			for(int j=3; j<board[i].length; j++)
			{
				if(board[i][j] != ' '
					&& board[i][j] == board[i+1][j-1]
					&& board[i][j] == board [i+2][j-2]
					&& board[i][j] == board[i+3][j-3])
				{
				return true;
				}
			}
		}
		boolean result=false;
		return result;
	}
}
