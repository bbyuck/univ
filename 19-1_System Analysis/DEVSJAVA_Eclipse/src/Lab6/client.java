package Lab6;
import simView.*;
import genDevs.modeling.*;
import GenCol.*;

public class client extends ViewableAtomic
{
	protected request req_msg;
	protected result res_msg;
	protected double int_arr_time;
	protected int count;
  
	private int num1;
	private int num2;
	private char[] op_arr = {'+', '-', '*', '%'};
	
	public client() 
	{
		this("genr", 30);
	}
  
	public client(String name, double Int_arr_time)
	{
		super(name);
   
		addOutport("out");
		addInport("in");
    
		int_arr_time = Int_arr_time;
	}
  
	public void initialize()
	{
		count = 1;
		req_msg = new request("none", 0, 0, ' ');
		res_msg = new result("none", 0);
		num1 = 0;
		num2 = 0;
		holdIn("active", int_arr_time);
	}
  
	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("active"))
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "in", i))
				{
					res_msg = (result)x.getValOnPort("in", i);
					System.out.println("result : " + res_msg.result);
				
				}
			}
		}
	}

	public void deltint()
	{
		if (phaseIs("active"))
		{
			//0 <= Math.random() < 1
			num1 = (int)(Math.random() * 100) + 1;
			num2 = (int)(Math.random() * 100) + 1;
			char op = op_arr[(int)(Math.random() * 4)];
			req_msg = new request((Integer.toString(num1) + op + Integer.toString(num2)), num1, num2, op); // string 자동 형변환 됨
			holdIn("active", int_arr_time);
		}
	}

	public message out() // out은 나온다
	{
		message m = new message();
		if(phaseIs("active")) {
			m.add(makeContent("out", req_msg));
		}
		return m;
	}
  
	public String getTooltipText() // 기말에 안나옴
	{
		return
        super.getTooltipText()
        + "\n" + "job: " + req_msg.getName();
	}
}
