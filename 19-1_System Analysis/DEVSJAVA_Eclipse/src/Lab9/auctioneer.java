package Lab9;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class auctioneer extends ViewableAtomic
{
	protected int[] bid_list;		// �� customer���� customer id(�迭�� index) bidding price(element)���夤
	protected int customer_number; // customer��
	protected int count; // �޼��� �� -> ��� ������ �ִ� ���
	protected auction_msg auction;
	protected String max_bidder;	// ���� ū bidding�� �� customer
	protected int max_price;
	protected String end_bidder;	// ���� bid ���Ŀ� ���� bidder
	protected int end_price;		// ���� ��������
	
	protected int customer_counter;	// customer number�� ���Ͽ� round ���� �ñ� ������ �� �� ����
	
	public auctioneer()		//�⺻������
	{
		this("auctioneer", 20);
	}

	public auctioneer(String name, int _customer_number)		//������ �����ε�
	{
		super(name);
    
		customer_number = _customer_number;
		addInport("product_in");	// supplier�� ���� start msg ���� inport
		addInport("bid_in"); 		// customer�� ���� bid_msg ���� in 
		
		addOutport("start");		// customer�鿡�� ��� ������ �˸��� msg outport
		addOutport("result_out");	// supplier���� ��� ���Ḧ �˸��� msg outport
		addOutport("bid_out");		// customer�鿡�� round�� bid_msg�� ������ outport
	}
  
	public void initialize()
	{
		bid_list = new int[customer_number + 1];	// customer�� 1������
		customer_counter= 0;
		count = 0;
		max_bidder = "0";
		max_price = 0;
		end_bidder = "0";
		end_price = 0;
		
		
		holdIn("wait", INFINITY);
	}

	public void deltext(double e, message x)
	{
		Continue(e);
		if (phaseIs("wait"))  // auctioneer�� wait state�̸�
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "product_in", i)) 						 						// ��� ������product_in port�� ���� start msgȮ��
				{
					auction = (auction_msg)x.getValOnPort("product_in", i);							// start_msg�� auction_msg ������ ����� ����ȯ					
					System.out.println(auction.getName() + ": init_price " + auction.post_price);
					holdIn("start", 0); 		// supplier�κ��� start msg�� ������ wait -> start state�� transition 0 time�����̹Ƿ� �ٷ� internal function����
				}
			}
		}
		else if (phaseIs("bidding")) 										// bidding state
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "bid_in", i))
				{
					bid_msg temp;
					temp = (bid_msg)x.getValOnPort("bid_in", i); // bid_msg�κ��� bid ���� ������������
					bid_list[temp.customer_id] = temp.bidding_price;	// bid list �迭�� customer_id�� idx�� �Ͽ� �� customer���� bidding_price����
					
					System.out.println("customer#" + temp.customer_id + ": " + temp.bidding_price);
					
					customer_counter++;			// customer_number�� �������� ����� ��������
					if(customer_counter == customer_number) { // customer number�� 5�� ������ �ִ� ã��
						customer_counter = 0;
						
						max_price = bid_list[1];			  // �ִ� ���ϱ� ���� setting -> linear search
						max_bidder = "1";
						for(int j = 2; j < customer_number + 1; j++) {
							if(max_price < bid_list[j]) {
								max_price = bid_list[j];
								max_bidder = Integer.toString(j);
							}
						}
					
						auction.post_price = max_price;
						count++;
						
						System.out.println("\nstage " + count);
						System.out.println("customer# " + max_bidder + " is winner");
						
						if(count == 5) { // ��� ���� 5�� ī��Ʈ 5�� ������ sent state, 5���� �Ǹ� result state						count = 0;
							holdIn("result", 0);
						}
						else {		//�� ������ sent�� transition
							holdIn("sent", 0);
						}
					}
				}
			}
		}
	}
  
	public void deltint()
	{
		if (phaseIs("start"))
		{	
			holdIn("bidding", INFINITY); // ���� auctioneer�� state�� start �����̸� ���� transition�� �߻��� �� ���� bidding ���·� holdIn�Ѵ�
		}
			else if(phaseIs("sent")) {	 
			holdIn("bidding", INFINITY); // ���� auctioneer�� state�� sent �����̸� ���� transition�� �߻��� �� ���� bidding ���·� holdIn�Ѵ�
		}
		else if(phaseIs("result")) {	// ��� bidding round�� ��ģ �� result ���°� �Ǹ�
			end_bidder = max_bidder;	// �ְ��� bidding �� bidder�� ���� bidder�� set
			end_price = max_price;		// ���� ������ �ְ��� set
			
			System.out.println(": winner is customer#" + end_bidder + ", result price is " + end_price);
			holdIn("wait", INFINITY);		// internal function�� job�� �����ϰ� wait ���·� holdIn
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("start")) 		//start ���¿��� out function
		{
			m.add(makeContent("start", new auction_msg("auction_msg #a(start)", auction.post_price)));		// auction_msg(start) out
		}
		if (phaseIs("sent")) 		//sent ���¿��� out function
		{
			m.add(makeContent("bid_out", new auction_msg("auction_msg #a(sent)", auction.post_price)));		// auction_msg(sent) out
		}
		if (phaseIs("result")) 		//result ���¿��� out function
		{
			m.add(makeContent("result_out", new auction_msg("auction_msg #a(result)", max_price)));			// auction_msg(result) out
		}
		return m;
	}
}

