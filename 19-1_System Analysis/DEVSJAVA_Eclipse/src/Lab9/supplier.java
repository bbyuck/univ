package Lab9;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class supplier extends ViewableAtomic
{
  
	protected int initial_price;
	
	public supplier()
	{
		this("supplier", 2000);
	}

	public supplier(String name, int _initial_price)
	{
		super(name);
    
		initial_price = _initial_price;
		
		addOutport("product_out");
		addInport("result_in");
		
	}
  
	public void initialize()
	{	
		holdIn("start", 0);
	}

	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("wait")) // phase가 passive일때만 job을 받음
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "result_in", i))
				{	
					holdIn("finished", INFINITY);
				}
			}
		}
	}
  
	public void deltint()
	{
		if (phaseIs("start"))
		{
			holdIn("wait", INFINITY); // 다음 external이 들어올 때 까지 passive상태를 유지한다
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("start"))
		{
			m.add(makeContent("product_out", new auction_msg("start", initial_price)));
		}
		return m;
	}

}

