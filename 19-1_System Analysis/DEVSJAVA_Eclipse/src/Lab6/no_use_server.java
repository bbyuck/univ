package Lab6;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class no_use_server extends ViewableAtomic
{
	protected no_use_request req_msg;
	protected no_use_result res_msg;
	protected int result;
	protected double processing_time;

	public no_use_server()
	{
		this("proc", 20);
	}

	public no_use_server(String name, double Processing_time)
	{
		super(name);
    
		addInport("in");
		addOutport("out");
		
		processing_time = Processing_time;
	}
  
	public void initialize()
	{
		
		req_msg = new no_use_request("none", 0, 0 );
		res_msg = new no_use_result("none", 0);
		result = 0;
		holdIn("passive", INFINITY);
	}

	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("passive")) // phase가 passive일때만 job을 받음
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "in", i))
				{
					req_msg = (no_use_request)x.getValOnPort("in", i);
					result = req_msg.num1 + req_msg.num2;
					res_msg = new no_use_result(Integer.toString(result), result);
					holdIn("busy", processing_time);
				}
			}
		}
	}
  
	public void deltint()
	{
		if (phaseIs("busy"))
		{
			req_msg = new no_use_request("none", 0, 0);
			res_msg = new no_use_result("none", 0);
			holdIn("passive", INFINITY); // 다음 external이 들어올 때 까지 passive상태를 유지한다
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("busy"))
		{
			m.add(makeContent("out", res_msg));
		}
		return m;
	}

	public String getTooltipText()
	{
		return
		super.getTooltipText()
		+ "\n" + "job: " + res_msg.getName();
	}

}

