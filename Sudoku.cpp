#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

bool check9(int* arr, int size)
{
    if (size != 9)
    {
        cout << "\n9false\n";
        return false;
    }

    int i;
    set <int> s;
    for(i=0; i<9; i++)
    {
        if(arr[i] != 0)
        {
            if(s.insert(arr[i]).second == false || arr[i] > 9 || arr[i] < 1)
            {
                return false;
            }
        }
    }
    return true;
}

class Sudoku
{
    private:
        int difficulty;
        int SUDO[9][9];
        int solSUDO[9][9];
        bool rowSUDO[9];
        bool colSUDO[9];
        bool blockSUDO[9];
        
    public:
        Sudoku()
        {
            difficulty = 1;
            for (int i = 0; i<9; i++) {
                for (int j = 0; j<9; j++) {
                    SUDO[i][j] = -1;
                    solSUDO[i][j] = -1;
                }
                rowSUDO[i] = false;
                colSUDO[i] = false;
                blockSUDO[i] = false;
            }
        }
        void copy()
        {
            int i,j;
            for(i =0; i<9; i++)
            {
                for(j=0; j<9; j++)
                {
                    SUDO[i][j] = solSUDO[i][j];
                }
            }
        }
        void insertSUDO(int data, int r, int c)
        {
            SUDO[r][c] = data;
        }
        void insertSolSUDO(int data, int r, int c)
        {
            solSUDO[r][c] = data;
        }
        void displaySUDO(int r, int c)
        {
            if (SUDO[r][c] == -1)
                cout << "_  ";
            else 
                cout << SUDO[r][c] << "  ";
        }
        void displaySolSUDO(int r, int c)
        {
            if (solSUDO[r][c] == -1)
                cout << "_  ";
            else 
                cout << solSUDO[r][c] << "  ";
        }
        void printSUDO()
        {
            system("CLS");
            cout << "\n==========================\n\n";
            for (int i = 0; i<9; i++) {
                for (int j = 0; j<9; j++)
                    displaySUDO(i, j);
                cout << "\n\n";
            }
            cout << "\n==========================\n";
        }
        void printSolSUDO()
        {
            system("CLS");
            cout << "\n==========================\n\n";
            for (int i = 0; i<9; i++) {
                for (int j = 0; j<9; j++)
                    displaySolSUDO(i, j);
                cout << "\n\n";
            }
            cout << "\n==========================\n";
        }
        bool boxSafe(int data, int rowStart, int colStart) 
        { 
            for (int i = 0; i<3; i++) 
                for (int j = 0; j<3; j++) 
                    if (SUDO[rowStart+i][colStart+j] == data) 
                        return false; 
            return true; 
        } 
        bool rowSafe(int data, int i) 
        { 
            for (int j = 0; j<9; j++) 
                if (SUDO[i][j] == data) 
                    return false; 
            return true; 
        } 
        bool colSafe(int data, int j) 
        { 
            for (int i = 0; i<9; i++) 
                if (SUDO[i][j] == data) 
                    return false; 
            return true; 
        } 
        bool CheckIfSafe(int data, int i, int j) 
        { 
                return (rowSafe(data, i) && colSafe(data, j) && boxSafe(data, i-i%3, j-j%3));          
        } 
        bool gridAvailable(int i, int j)
        {
            if (SUDO[i][j] == -1)
                return true;
            else
                return false;                   
        }

        bool boxSafeSol(int data, int rowStart, int colStart) 
        { 
            for (int i = 0; i<3; i++) 
                for (int j = 0; j<3; j++) 
                    if (solSUDO[rowStart+i][colStart+j] == data) 
                        return false; 
            return true; 
        } 
        bool rowSafeSol(int data, int i) 
        { 
            for (int j = 0; j<9; j++) 
                if (solSUDO[i][j] == data) 
                    return false; 
            return true; 
        } 
        bool colSafeSol(int data, int j) 
        { 
            for (int i = 0; i<9; i++) 
                if (solSUDO[i][j] == data) 
                    return false; 
            return true; 
        } 
        bool CheckIfSafeSol(int data, int i, int j) 
        { 
                return (rowSafeSol(data, i) && colSafeSol(data, j) && boxSafeSol(data, i-i%3, j-j%3));          
        } 
        bool gridAvailableSol(int i, int j)
        {
            if (solSUDO[i][j] == -1)
                return true;
            else
                return false;                   
        }
        bool checkSUDOKU()
        {
            int A[9], B[9];
            for (int i = 0; i<9; i++)
            {
                rowSUDO[i] = check9(SUDO[i], 9);
                for (int a = 0; a<9; a++)
                {
                    A[a] = SUDO[i][a];
                }
                colSUDO[i] = check9(A, 9);
            }
            int p = 0, q = 0, ctr = 0;
            for (int k = 0; k<9; k++)
            {
                for (int i = 0; i<3; i++)
                {
                    for (int j = 0; j<3; j++)
                    {
                        B[i*3+j] = SUDO[i + p][j + q];
                    }
                }
                blockSUDO[k] = check9(B, 9); ctr++;
                if (ctr%3 == 0)
                {
                    p += 3;
                    q = 0;
                }
                else
                    q += 3;
            }

            bool TRUTH = true;
            for (int i = 0; i<9; i++)
                TRUTH *= rowSUDO[i];
            for (int i = 0; i<9; i++)
                TRUTH *= colSUDO[i];
            for (int i = 0; i<9; i++)
                TRUTH *= blockSUDO[i];

            return TRUTH;
        }
} S;

int MAIN_MENU()
{
    system("CLS");
    int diff = 0;

    cout << "\n=================================SUDOKU==================================\n";
    cout << "\nWelcome to SUDOKU - Object Oriented Programming Lab miniProject";
    cout << "\n<*for a more immersive experience, it is advised to run this code*>";
    cout << "\n<*in a separate .exe output window rather to using the default terminal*>";
    cout << "\n<*provided by the respective text editor / IDE after compilation.*>\n";
    cout << "\n#1. Swagat S. Bhuyan \n\tROLLNO.: 18-1-5-059\n\tSEM: IV\n\tDEPTT: Computer Science and Engineering";
    cout << "\n#2. Mayur Raj Bharati \n\tROLLNO.: 18-1-5-026\n\tSEM: IV\n\tDEPTT: Computer Science and Engineering";
    cout << "\n\nChoose Difficulty of Sudoku Level: ";
    cout << "\n\t1. EASY.";
    cout << "\n\t2. MEDIUM.";
    cout << "\n\t3. HARD.";
    cout << "\n\t4. SANDBOX MODE.\n";
    cout << "(enter index number of corresponding difficulty level): "; 
    cin >> diff;
    
    system("PAUSE");
    return diff;
}

set <int> RefillSet(set <int> s)
{
    s.insert(1);
    s.insert(2);
    s.insert(4);
    s.insert(9);
    s.insert(3);
    s.insert(6);
    s.insert(7);
    s.insert(5);
    s.insert(8);   
    return s;
}

bool RemainingGridFill(int i, int j)
{
    if (i>=9 && j>=9) 
        return true; 

    if (j>=9 && i<8) 
    { 
        i = i + 1; 
        j = 0; 
    } 
  
    if (i < 3) 
    { 
        if (j < 3) 
            j = 3; 
    } 
    else if (i < 6) 
    { 
        if (j==(int)(i/3)*3) 
            j =  j + 3; 
    } 
    else
    { 
        if (j == 6) 
        { 
            i = i + 1; 
            j = 0; 
            if (i>=9) 
                return true; 
        } 
    } 
  
    for (int data = 1; data<=9; data++) 
    { 
        if (S.CheckIfSafeSol(data, i, j)) 
        { 
            S.insertSolSUDO(data, i, j); 
            if (RemainingGridFill(i, j+1)) 
                return true; 
  
            S.insertSolSUDO(-1, i, j);  
        } 
    } 

    return false; 
}


void SolutionGrid()
{
    srand(time(0)); 
    set <int> s = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    for (int i = 0; i<3; i++)
    {
        for (int j = 0; j<3; j++)
        {
            int ctr = 0;
            while (ctr == 0)
            {
                int r = rand()%9 + 1;
                if (s.find(r) != s.end())
                {
                    S.insertSolSUDO(r, i, j);
                    s.erase(r);
                    ctr = 1;
                }
            }
        }
    }
    s = RefillSet(s);
    for (int i = 3; i<6; i++)
    {
        for (int j = 3; j<6; j++)
        {
            int ctr = 0;
            while (ctr == 0)
            {
                int r = rand()%9 + 1;
                if (s.find(r) != s.end())
                {
                    S.insertSolSUDO(r, i, j);
                    s.erase(r);
                    ctr = 1;
                }
            }
        }
    }
    s = RefillSet(s);
    for (int i = 6; i<9; i++)
    {
        for (int j = 6; j<9; j++)
        {
            int ctr = 0;
            while (ctr == 0)
            {
                int r = rand()%9 + 1;
                if (s.find(r) != s.end())
                {
                    S.insertSolSUDO(r, i, j);
                    s.erase(r);
                    ctr = 1;
                }
            }
        }
    }
    RemainingGridFill(0, 3);
}

void Remove_elements(int diff)
{
    srand(time(0));
    int i;
    S.copy();
    if(diff == 1)
    {
        for(i=0; i<10; i++)
        {
            int r = rand()%9 + 1;
            int c = rand()%9 + 1;
            S.insertSUDO(-1, r, c);
        }
    }
    else if(diff ==2)
    {
        for(i=0;i<20;i++)
        {
            int r = rand()%9 + 1;
            int c = rand()%9 + 1;
            S.insertSUDO(-1, r, c);
        }
    }
    else
    {
        for(i=0; i<30; i++)
        {
            int r = rand()%9 + 1;
            int c = rand()%9 + 1;
            S.insertSUDO(-1, r, c);
        }
    }

}

void EnterValues()
{
	int ctr =0, row, col, data;
	while(ctr == 0)
	{
        cout<<"\n<*In this screen, edit the Sudoku table above using coordinates below*>";
        cout<<"\n<*You may enter new values or edit the existing Sudoku Table, also exit.*>";
		cout<<"\nPlease enter row value and column value whose data you want to enter:"<<endl;
		cin>>row>>col;
		cout<<"Enter data(between 1-9):"<<endl;
		cin>>data;
        if (data > 9 || data < 1)
        {
            cout << "\n*INVALID* try again.....";
            continue;
        }
        Beep((data+1)*100, 200);
		S.insertSUDO(data, row-1, col-1);
    
      BRUH:
		S.printSUDO();
		cout<<"Press 0 if you wish to continue:"<<endl;
		cin>>ctr;
		system("CLS");
		S.printSUDO();
	}
}

int main()
{
    int data, diff, help = 0;

    diff = MAIN_MENU();  
    
    SolutionGrid();

    if (diff != 4)
        Remove_elements(diff);  

    S.printSUDO();  

    EnterValues();

    if(S.checkSUDOKU() == 1)
    {
        Beep(700, 200);
        Beep(750, 200);
        Beep(900, 400);
    	cout<<"YOU WON THE GAME!"<<endl;
    }
    else
    {
        Beep(450, 200);
        Beep(400, 200);
        Beep(200, 400);
    	cout<<"GAME OVER!"<<endl;
    }
    
    system("PAUSE");

    return 0;
}