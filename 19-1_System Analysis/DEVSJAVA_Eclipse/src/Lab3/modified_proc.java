package Lab3;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class modified_proc extends ViewableAtomic
{
  
	protected entity job; // job을 받을 메모리
	protected double processing_time; 

	public modified_proc()
	{
		this("proc", 40);
	}

	public modified_proc(String name, double Processing_time)
	{
		super(name);
		
		addInport("in");
		addOutport("out");
		
		processing_time = Processing_time;
	}
  
	public void initialize()
	{
		job = new entity(""); // job의 이름
		
		holdIn("passive", INFINITY); // 강의노트 슈도코드에서 phase busy 아니고 passive, INFINITY는 devs키워드
	}

	public void deltext(double e, message x)
	{
		Continue(e); // e는 devs 키워드
		if (phaseIs("passive"))
		{
			for (int i = 0; i < x.getLength(); i++) // 시험에서는 함수는 써줌
			{
				if (messageOnPort(x, "in", i))
				{
					job = x.getValOnPort("in", i);
					
					holdIn("busy", processing_time);
				}
			}
		}
	}
  
	public void deltint() // out function이 끝나고 internal이 불려질 때 busy 상태를 passive 상태로 transition
	{
		if (phaseIs("busy"))
		{
			job = new entity("");
			holdIn("passive", INFINITY);
		}
	}

	public message out()
	{
		message m = new message();
		
		if(phaseIs("busy")) {
			m.add(makeContent("out", job)); // generator의 경우는 job을 생성해야하므로 entity가 길다. processor는 괜찮음.
		}
		
		return m;
	}

	public String getTooltipText()
	{
		return
		super.getTooltipText()
		+ "\n" + "job: " + job.getName();
	}

}

