package Lab9;
import java.awt.*;
import simView.*;

public class auction extends ViewableDigraph
{

	
	final int CUSTOMER = 5;
	final int INITIAL_PRICE = 2000;
	
	public auction()
	{
		super("auction");
    	
		int[] pe_table = {0, 240, 220, 260, 300, 280};//
		int[] mbp_table = {0, // 최대값 boundary 지정을 위한 배열
				(int)(INITIAL_PRICE * 2.0),
				(int)(INITIAL_PRICE *  2.2),
				(int)(INITIAL_PRICE * 1.9),
				(int)(INITIAL_PRICE * 2.4),
				(int)(INITIAL_PRICE * 2.1)};
		
		ViewableAtomic s = new supplier("supplier", INITIAL_PRICE); //
		ViewableAtomic a = new auctioneer("auctioneer", CUSTOMER);//
		
		add(s);
		add(a);
		
		addCoupling(s, "product_out", a, "product_in");//
		addCoupling(a, "result_out", s, "result_in");//
		
		for(int i = 1; i <= CUSTOMER; i++) { // 
			ViewableAtomic c = new customer("customer" + i, pe_table[i], mbp_table[i], i);
			add(c);
			
			addCoupling(a, "result_out", c, "result_in");
			addCoupling(a, "start", c, "start");
			addCoupling(a, "bid_out", c, "bid_in");
			addCoupling(c, "bid_out", a, "bid_in");
			
		}
	}

    
    /**
     * Automatically generated by the SimView program.
     * Do not edit this manually, as such changes will get overwritten.
     */
    public void layoutForSimView()
    {
        preferredSize = new Dimension(988, 646);
        ((ViewableComponent)withName("auctioneer")).setPreferredLocation(new Point(289, 283));
        ((ViewableComponent)withName("customer2")).setPreferredLocation(new Point(630, 178));
        ((ViewableComponent)withName("customer3")).setPreferredLocation(new Point(628, 260));
        ((ViewableComponent)withName("customer5")).setPreferredLocation(new Point(633, 477));
        ((ViewableComponent)withName("customer1")).setPreferredLocation(new Point(627, 105));
        ((ViewableComponent)withName("supplier")).setPreferredLocation(new Point(-11, 324));
        ((ViewableComponent)withName("customer4")).setPreferredLocation(new Point(623, 350));
    }
}
