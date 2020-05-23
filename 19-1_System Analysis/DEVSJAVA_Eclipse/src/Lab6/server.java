package Lab6;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class server extends ViewableAtomic
{
	
	protected Queue q; // 큐 선언은 뎁스 큐니깐 필요는 없음
	protected request req_msg;
	protected result res_msg;
	protected int result;
	protected double processing_time;
	public server()
	{
		this("Server", 20);
	}

	public server(String name, double Processing_time)
	{
		super(name);
    
		addInport("in");
		addOutport("out");
		
		processing_time = Processing_time;
	}
	
	public void initialize()
	{
		q = new Queue();
		req_msg = new request("none", 0, 0, ' ');
		res_msg = new result("none", 0);
		result = 0;
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
					req_msg = (request)x.getValOnPort("in", i);
					switch(req_msg.op) {
					case '+':
						result = req_msg.num1 + req_msg.num2;
						processing_time = 10;
						break;
					case '-':
						result = req_msg.num1 - req_msg.num2;
						processing_time = 20;
						break;
					case '*':
						result = req_msg.num1 * req_msg.num2;
						processing_time = 40;
						break;
					case '%':
						result = req_msg.num1 % req_msg.num2;
						processing_time = 50;
						break;
					default:
						break;
					}
					res_msg = new result(Integer.toString(result), result);
					holdIn("busy", processing_time);
					System.out.println(Integer.toString(req_msg.num1) + req_msg.op + Integer.toString(req_msg.num2));
				}
			}
		}
		else if (phaseIs("busy"))
		{
			for (int i = 0; i < x.size(); i++)
			{
				if (messageOnPort(x, "in", i))
				{
					request temp = (request)x.getValOnPort("in", i);
					q.add(temp); 
					System.out.println(q);
				}
			}
		}
	}
	

	public void deltint()
	{
		if (phaseIs("busy"))
		{
			if (!q.isEmpty())
			{
				req_msg = (request)q.removeFirst();
				switch(req_msg.op) {
				case '+':
					result = req_msg.num1 + req_msg.num2;
					processing_time = 10;
					break;
				case '-':
					result = req_msg.num1 - req_msg.num2;
					processing_time = 20;
					break;
				case '*':
					result = req_msg.num1 * req_msg.num2;
					processing_time = 40;
					break;
				case '%':
					result = req_msg.num1 % req_msg.num2;
					processing_time = 50;
					break;
				default:
					break;
				}
				res_msg = new result(Integer.toString(result), result);
				holdIn("busy", processing_time);
			}
			else
			{
				req_msg = new request("none", 0, 0, ' ');
				res_msg = new result("none", 0);
				holdIn("passive", INFINITY);
			}
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
        + "\n" + "queue length: " + q.size()
        + "\n" + "queue itself: " + q.toString();
	}

}



