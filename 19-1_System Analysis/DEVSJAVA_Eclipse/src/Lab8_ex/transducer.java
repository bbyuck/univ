package Lab8_ex;
import simView.*;
import genDevs.modeling.*;
import GenCol.*;

public class transducer extends  ViewableAtomic
{
	
	protected Function arrived, solved;
	protected double clock, total_ta, observation_time;
	int node;
	int loss;

	public transducer(String name, double Observation_time, int _node)
	{
		super(name);
    
		addOutport("out");
		addInport("ariv");
		addInport("solved");
		addInport("loss");
    
		arrived = new Function();
		solved = new Function();
    
		observation_time = Observation_time;
		
		node = _node;
	}
  
	public transducer()
	{
		this("transd", 200, 5);
	}

	public void initialize()
	{
		holdIn("on", observation_time);
		
		clock = 0;
		total_ta = 0;
		loss = 0;
    
		arrived = new Function();
		solved = new Function();
		
	}

	public void deltext(double e, message x)
	{
		clock = clock + e;
		Continue(e);
		entity val;
 
		if(phaseIs("on"))
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (messageOnPort(x, "ariv", i))
				{
					val = x.getValOnPort("ariv", i);
					arrived.put(val.getName(), new doubleEnt(clock));
				}
				if (messageOnPort(x, "solved", i))
				{
					val = x.getValOnPort("solved", i);
					if (arrived.containsKey(val.getName()))
					{
						entity ent = (entity) arrived.assoc(val.getName());
					
						doubleEnt num = (doubleEnt) ent;
						double arrival_time = num.getv();
          
						double turn_around_time = clock - arrival_time;
          
						total_ta = total_ta + turn_around_time;
          
						solved.put(val, new doubleEnt(clock));
					}
				}
				if (messageOnPort(x, "loss", i))
				{
					loss++;
				}
				
			}
			show_state();
		}
	}

	public void deltint()
	{
		if(phaseIs("on")) {
			clock = clock + sigma;
			System.out.println("--------------------------------------------------------");
	   		show_state();
	   		System.out.println("--------------------------------------------------------");
	   		holdIn("off", 0);	
		}
	}
  
	public message out()
	{
		message m = new message();
		content con = makeContent("out", new entity("TA: " + compute_TA()));
		m.add(con);
		return m;
	}

	public double compute_TA()
	{
		double avg_ta_time = 0;
		if (!solved.isEmpty())
		{
			avg_ta_time = ( (double) total_ta) / solved.size();
		}
		return avg_ta_time;
	}

  
	public String compute_Thru()
	{
		String thruput = "";
		if (clock > 0)
		{
			thruput = solved.size() + " / " + clock;
		}
		return thruput;
	}

	public void show_state()
	{
		System.out.println("state of  " + name + ": ");
		System.out.println("phase, sigma : " + phase + " " + sigma + " ");
		
		if (arrived != null && solved != null)
		{
			System.out.println("Total jobs arrived : "+ arrived.size());
			System.out.println("Total jobs solved : " + solved.size());
			System.out.println("AVG TA = " + compute_TA());
			System.out.println("THRUPUT = " + compute_Thru());
			System.out.println("loss rate: " + loss + "/" + arrived.size());
			System.out.println();
		}
	}	
  
	public String getTooltipText()
	{
		String s = "";
		if (arrived != null && solved != null)
		{
			s = "\n" + "jobs arrived :" + arrived.size()
			+ "\n" + "jobs solved :" + solved.size()
			+ "\n" + "AVG TA = " + compute_TA()
			+ "\n" + "THRUPUT = " + compute_Thru();
		}
		return super.getTooltipText() + s;
	}

}
