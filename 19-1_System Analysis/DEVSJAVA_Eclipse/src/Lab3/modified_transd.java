package Lab3;
import simView.*;
import genDevs.modeling.*;
import GenCol.*;

public class modified_transd extends  ViewableAtomic
{
	
	protected Function arrived, solved; // list or hashtable 그냥 객체
	protected double clock, total_ta, observation_time;

	public modified_transd(String name, double Observation_time)
	{
		super(name);
    
		addOutport("out");
		addInport("ariv"); // arrive -> 생성된 job (from genr)
		addInport("solved"); // arrive -> 완료된 job (from proc)
    
		arrived = new Function();
		solved = new Function();
    
		observation_time = Observation_time;
	}
  
	public modified_transd()
	{
		this("transd", 200);
	}

	public void initialize()
	{	
		clock = 0;
		total_ta = 0; // double
    
		arrived = new Function();
		solved = new Function();
		
		holdIn("on", observation_time);
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
					arrived.put(val.getName(), new doubleEnt(clock)); // val.getName(): key , doble clock: value
				}
				if (messageOnPort(x, "solved", i))
				{
					val = x.getValOnPort("solved", i);
					if (arrived.containsKey(val.getName()))
					{
						entity ent = (entity) arrived.assoc(val.getName()); 
						doubleEnt num = (doubleEnt) ent; // 형변환 그닥 중요하지 않음
						
						
						double arrival_time = num.getv(); // getv()를 통해 arrival_time을 받아오는게 중요
          
						double turn_around_time = clock - arrival_time;
          
						total_ta = total_ta + turn_around_time;
          
						solved.put(val, new doubleEnt(clock));
					}
				}
			}
			show_state();
		}
	}

	public void deltint()
	{
		if (phaseIs("on"))
		{
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
		
		if (phaseIs("on"))
		{
			m.add(makeContent("out", new entity("TA: " + compute_TA())));
		}
		
		return m;
	}

	public double compute_TA()
	{
		double avg_ta_time = 0;
		if (!solved.isEmpty())
		{
			avg_ta_time = ( (double) total_ta) / solved.size(); // 실제 계산부분
		}
		return avg_ta_time;
	}
	
	public double coupute_TOTAL_TA() {
		double total_ta_time = 0;
		if(!solved.isEmpty()) {
			total_ta_time = ((double)total_ta);
		}
		return total_ta_time;
	}
  
	public String compute_Thru()
	{
		String thruput = "";
		if (clock > 0)
		{
			thruput = solved.size() + " / " + clock; // string
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
		}
	}	
  
	public String getTooltipText() // 시험에 안 나옴
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
