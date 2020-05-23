package SimpArc;
import java.awt.*;
import simView.*;

public class gpt extends ViewableDigraph
{

	public gpt()
	{
		super("gpt");
    	
		ViewableAtomic g = new genr("g", 30);
		ViewableAtomic p = new proc("p", 20);
		ViewableAtomic t = new transd("t", 1000);
    	
		add(g);
		add(p);
		add(t);
  
		addCoupling(g, "out", p, "in");
		addCoupling(g, "out", t, "ariv");
		
		addCoupling(p, "out", t, "solved");
     
		addCoupling(t, "out", g, "in");
	}

    
    /**
     * Automatically generated by the SimView program.
     * Do not edit this manually, as such changes will get overwritten.
     */
    public void layoutForSimView()
    {
        preferredSize = new Dimension(988, 646);
        ((ViewableComponent)withName("p")).setPreferredLocation(new Point(396, 373));
        ((ViewableComponent)withName("t")).setPreferredLocation(new Point(339, 55));
        ((ViewableComponent)withName("g")).setPreferredLocation(new Point(115, 185));
    }
}
