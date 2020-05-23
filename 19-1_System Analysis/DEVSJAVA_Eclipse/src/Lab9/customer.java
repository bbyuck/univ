package Lab9;
import genDevs.modeling.*;

import java.util.Random;

import GenCol.*;
import simView.*;

public class customer extends ViewableAtomic
{
  
	protected int bid_price;
	protected int price_elasticity;
	protected int max_bid_price;
	protected int posted_price;
	
	protected int customer_id;
	
	Random r = new Random();
	
	public customer()
	{
		this("customer", 200, 3000, 1);
	}

	public customer(String name, int _price_elasticity, int _max_bid_price, int _customer_id)
	{
		super(name);
    
		
		price_elasticity = _price_elasticity;
		max_bid_price = _max_bid_price;
		customer_id = _customer_id;
	
		addInport("bid_in");
		addInport("result_in");
		addInport("start");
		
		addOutport("bid_out");
	}
  
	public void initialize()
	{
		posted_price = 0;
		bid_price = 0;
		
		holdIn("wait_1", INFINITY);
	}

	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("wait_1")) // phase가 passive일때만 job을 받음
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "start", i))
				{
					auction_msg temp;
					temp = (auction_msg)x.getValOnPort("start", i);
					posted_price = temp.post_price;
					bid_price = temp.post_price + (r.nextInt(price_elasticity) + 1);
					
					if(posted_price > max_bid_price) {
						bid_price = 0;
					}
					holdIn("bidding", 0);
				}
			}
		}
		else if (phaseIs("wait_2")) // phase가 passive일때만 job을 받음
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "bid_in", i))
				{
					auction_msg temp;
					temp = (auction_msg)x.getValOnPort("bid_in", i);
					posted_price = temp.post_price;
					bid_price = temp.post_price + (r.nextInt(price_elasticity) + 1);
					
					if(posted_price > max_bid_price) {
						bid_price = 0;
					}
					holdIn("bidding", 0);	
				}
				if(messageOnPort(x, "result_in" , i)) {
					holdIn("wait1", INFINITY);
				}
			}
		}
	}
  
	public void deltint()
	{
		if (phaseIs("bidding"))
		{
			
			holdIn("wait_2", INFINITY); // 다음 external이 들어올 때 까지 passive상태를 유지한다
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("bidding"))
		{
			m.add(makeContent("bid_out", new bid_msg("bid_msg #" + customer_id, customer_id, bid_price)));
		}
		return m;
	}

	public String getTooltipText()
	{
		return
		super.getTooltipText()
		+ "\n" + "pe: " + price_elasticity
		+ "\n" + "mbp: " + max_bid_price
		+ "\n" + "price: " + bid_price;
	}

}

