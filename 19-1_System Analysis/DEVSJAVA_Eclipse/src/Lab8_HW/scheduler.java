package Lab8_HW;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class scheduler extends ViewableAtomic
{
  
	protected entity job;
	protected double scheduling_time;
	protected int NODE;
	protected int outport_num;
	double[] q_size_list;
	double[] workload_list;
	double[] load_rate_list;
	

	public scheduler()
	{
//		this("proc", 0, 5, new double[5]);
		this("proc", 0, 5, new int[5]);
	}

//	public scheduler(String name, double Scheduling_time, int _node, double[] _q_size_list)
	public scheduler(String name, double Scheduling_time, int _node, int[] _q_size_list)
	{
		super(name);
    
		NODE = _node;
		q_size_list = new double[NODE+1];
		
		for(int i = 1; i <= NODE; i++) {
			q_size_list[i] = _q_size_list[i];
		}
		
		addInport("in");
		addOutport("out_loss");
		for(int i = 1; i <= NODE; i++) {
			addInport("in" + i);
			addOutport("out" + i);
		}
				
		scheduling_time = Scheduling_time;
	}
  
	public void initialize()
	{
		outport_num = 1;
		job = new entity("");
		holdIn("passive", INFINITY);
		
		workload_list = new double[NODE+1];
		load_rate_list = new double[NODE+1];
	}
	
	public void deltcon(double e, message x)
	{
		deltint();
		deltext(0, x);
	}	
	
	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("passive"))
		{			
//			"port: in1 message job1" 0
//			"port: in2 message job2" 1
			for (int i = 0; i < x.getLength(); i++)
			{
				for(int j = 1; j<=NODE; j++) {
					if(messageOnPort(x, "in"+j, i)) {
						workload_list[j]--;	
					}
				}
				
				if (messageOnPort(x, "in", i))
				{
					job = x.getValOnPort("in", i);
					
					System.out.println("Workload -");
					for(int j = 1; j <=NODE; j++) {
						
						load_rate_list[j] 
								= workload_list[j]*100 / q_size_list[j];
						System.out.println("\t processor" + j 
								+ ": " +load_rate_list[j] + "%");
					}
					
					//최소값의 위치 찾기
					outport_num = 1;
					double min_workload = load_rate_list[1];
					for(int j = 1; j <= NODE; j++) {
						if(min_workload > load_rate_list[j]) {
							min_workload = load_rate_list[j];
							outport_num = j;
						}
					}
					
					if(load_rate_list[outport_num] == 100) {
						System.out.println("!!! Can't Schedule " + job.getName());
						holdIn("loss", 0);
					}else {
						System.out.println("*processor" + outport_num + "* picked");
						holdIn("busy", scheduling_time);
					}
					System.out.println();
				}
			}
		}
	}
  
	public void deltint()
	{
		if(phaseIs("busy")){
			workload_list[outport_num]++;
			job = new entity("none");
			holdIn("passive", INFINITY);
		}
		else if(phaseIs("loss")) {
			holdIn("passive", INFINITY);
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("busy"))
		{
			m.add(makeContent("out"+outport_num, job));
		}
		else if(phaseIs("loss")) {
			m.add(makeContent("out_loss", job));
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

