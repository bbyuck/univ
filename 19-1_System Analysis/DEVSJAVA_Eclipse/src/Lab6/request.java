package Lab6;
import GenCol.*;

public class request extends entity
{   
	int num1, num2;
	char op;
	
	public request(String name, int _num1, int _num2, char _op)
	{  
		super(name); 
		
		num1 = _num1;
		num2 = _num2;
		op = _op;
		
	}
	
}

