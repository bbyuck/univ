package Lab3;
import simView.*;
import genDevs.modeling.*;
import GenCol.*;

public class modified_genr extends ViewableAtomic
{
	
	protected double int_arr_time;
	protected int count;
  
	public modified_genr() 
	{
		this("genr", 30);
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
//					holdIn("stop", INFINITY); // 외부에서 일이 들어오면 자동으로 stop상태로 천이되도록 job0가 끝나면서 output이 전달되면 trajectory가 멈추므로
				}
			}
		}
	}

	public void deltint()
	{
		if (phaseIs("active"))
		{
			if(count == 2 ) { // Job 2부터는  input sigma 50
				int_arr_time = 50;
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
