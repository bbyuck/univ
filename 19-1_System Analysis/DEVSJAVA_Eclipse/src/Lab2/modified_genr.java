package Lab2;
import simView.*;
import genDevs.modeling.*;
import GenCol.*;

public class modified_genr extends ViewableAtomic
{
	
	protected double int_arr_time;
	protected int count;
	
	public modified_genr() 
	{
		this("modified_genr", 40); // job0 sigma의 initial time = 40
	}
  
	public modified_genr(String name, double Int_arr_time)
	{
		super(name);
		
		addOutport("out");
		addInport("in");
		
		int_arr_time = Int_arr_time;
	}
  
	public void initialize()
	{
		count = 0;
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
					
				}
			}
		}
	}

	public void deltint()
	{
		if (phaseIs("active")) // active 상일때
		{
			if(count % 2 == 0) { // job count가 짝수->홀수로 넘어갈 때
				int_arr_time = 50;
			}
			else { // job count가 홀수->짝수로 넘어갈 때
				int_arr_time = 30;
			}
			count = count + 1;
			holdIn("active", int_arr_time);
		}
	}

	public message out()
	{
		message m = new message();
		m.add(makeContent("out", new entity("job" + count)));
		return m;
	}
  
	public String getTooltipText()
	{
		return
        super.getTooltipText()
        + "\n" + " int_arr_time: " + int_arr_time
        + "\n" + " count: " + count;
	}

}

