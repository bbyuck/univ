package Lab8_HW;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class processor extends ViewableAtomic
{
	
	protected Queue q;
	protected entity job;
	protected double processing_time;
	protected int size;
		
	public processor()
	{
		this("procQ", 20, 3);
	}

//	public processor(String name, double Processing_time, double _size)
	public processor(String name, double Processing_time, int _size)
	{
		super(name);
    
		addInport("in");
		addOutport("out");
		
//		size = (int)_size;
		size = _size;
		
		processing_time = Processing_time;
	}
	
	public void initialize()
	{
		q = new Queue();
		job = new entity("");
		holdIn("passive", INFINITY);
	}

	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("passive"))
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (messageOnPort(x, "in", i))
				{
					job = x.getValOnPort("in", i);
					
					holdIn("busy", processing_time);
				}
			}
		}
		else if (phaseIs("busy"))
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (messageOnPort(x, "in", i))
				{
					if(q.size() < size) {
						entity temp = x.getValOnPort("in", i);
						q.add(temp);	
					}
				}
			}
		}
	}
	
	// internal transition followed by external transition
	// internal -> external
	public void deltcon(double e, message x)
	{
		deltint();
		deltext(0, x);
	}	
	
	public void deltint()
	{
		if (phaseIs("busy"))
		{
			if (!q.isEmpty())
			{
				job = (entity) q.removeFirst();
				holdIn("busy", processing_time);
			}
			else
			{
				job = new entity("");
				holdIn("passive", INFINITY);
			}
		}
	}

	public message out()
	{
		message m = new message();
		
		if (phaseIs("busy"))
		{
			m.add(makeContent("out", job));
		}
		
		return m;
	}	
	
	public String getTooltipText()
	{
		return
        super.getTooltipText()
        + "\n" + "queue length: " + q.size()
        + "\n" + "queue itself: " + q.toString();
	}

}



