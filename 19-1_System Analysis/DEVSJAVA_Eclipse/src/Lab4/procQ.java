package Lab4;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class procQ extends ViewableAtomic
{
	
	protected Queue q; // java queue 아니고 devs queue
	protected entity job; // job을 받을 메모리
	protected double processing_time; 

	public procQ()
	{
		this("proc", 50);
	}

	public procQ(String name, double Processing_time)
	{
		super(name);
		
		addInport("in");
		addOutport("out");
		
		processing_time = Processing_time;
	}
  
	public void initialize()
	{
		q = new Queue(); // Queue 메모리 동적할당
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
		else if(phaseIs("busy")) {
			for (int i = 0; i < x.getLength(); i++) // 시험에서는 함수는 써줌
			{
				if (messageOnPort(x, "in", i))
				{
					entity temp = x.getValOnPort("in", i);
					q.add(temp);
				}
			}
		}
	}
  
	public void deltint() // out function이 끝나고 internal이 불려질 때 busy 상태를 passive 상태로 transition
	{
		if (phaseIs("busy"))
		{
			
			if(!q.isEmpty()) {
				job = (entity) q.removeFirst();
				
				holdIn("busy", processing_time);
			}
			else {
				job = new entity("");
				holdIn("passive", INFINITY);
			}
			
//			job = new entity("");
//			holdIn("passive", INFINITY);
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
			+ "\n" + "queue length: " + q.size()
			+ "\n" + "queue itself: " + q.toString();
	}

}

