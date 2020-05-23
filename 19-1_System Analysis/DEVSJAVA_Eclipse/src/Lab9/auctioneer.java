package Lab9;
import genDevs.modeling.*;
import GenCol.*;
import simView.*;

public class auctioneer extends ViewableAtomic
{
	protected int[] bid_list;		// 각 customer별로 customer id(배열의 index) bidding price(element)저장ㄴ
	protected int customer_number; // customer수
	protected int count; // 메세지 수 -> 모두 들어오면 최댓값 계산
	protected auction_msg auction;
	protected String max_bidder;	// 가장 큰 bidding을 한 customer
	protected int max_price;
	protected String end_bidder;	// 최종 bid 이후에 나온 bidder
	protected int end_price;		// 최종 낙찰가격
	
	protected int customer_counter;	// customer number와 비교하여 round 끝낼 시기 결정할 때 쓸 변수
	
	public auctioneer()		//기본생성자
	{
		this("auctioneer", 20);
	}

	public auctioneer(String name, int _customer_number)		//생성자 오버로딩
	{
		super(name);
    
		customer_number = _customer_number;
		addInport("product_in");	// supplier로 부터 start msg 받을 inport
		addInport("bid_in"); 		// customer로 부터 bid_msg 받을 in 
		
		addOutport("start");		// customer들에게 경매 시작을 알리는 msg outport
		addOutport("result_out");	// supplier에게 경매 종료를 알리는 msg outport
		addOutport("bid_out");		// customer들에게 round별 bid_msg를 보내는 outport
	}
  
	public void initialize()
	{
		bid_list = new int[customer_number + 1];	// customer는 1번부터
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
		if (phaseIs("wait"))  // auctioneer가 wait state이면
		{
			for (int i = 0; i < x.getLength(); i++)
			{
				if (messageOnPort(x, "product_in", i)) 						 						// 들어 오는지product_in port로 들어온 start msg확인
				{
					auction = (auction_msg)x.getValOnPort("product_in", i);							// start_msg를 auction_msg 형으로 명시적 형변환					
					System.out.println(auction.getName() + ": init_price " + auction.post_price);
					holdIn("start", 0); 		// supplier로부터 start msg를 받으면 wait -> start state로 transition 0 time동안이므로 바로 internal function으로
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
					temp = (bid_msg)x.getValOnPort("bid_in", i); // bid_msg로부터 bid 값을 가져오기위해
					bid_list[temp.customer_id] = temp.bidding_price;	// bid list 배열에 customer_id를 idx로 하여 각 customer마다 bidding_price저장
					
					System.out.println("customer#" + temp.customer_id + ": " + temp.bidding_price);
					
					customer_counter++;			// customer_number와 같아지면 결과를 내기위해
					if(customer_counter == customer_number) { // customer number가 5개 꽉차면 최댓값 찾기
						customer_counter = 0;
						
						max_price = bid_list[1];			  // 최댓값 구하기 위해 setting -> linear search
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
						
						if(count == 5) { // 비드 갯수 5개 카운트 5개 이전엔 sent state, 5개가 되면 result state						count = 0;
							holdIn("result", 0);
						}
						else {		//그 이전엔 sent로 transition
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
			holdIn("bidding", INFINITY); // 현재 auctioneer의 state가 start 상태이면 다음 transition이 발생할 때 까지 bidding 상태로 holdIn한다
		}
			else if(phaseIs("sent")) {	 
			holdIn("bidding", INFINITY); // 현재 auctioneer의 state가 sent 상태이면 다음 transition이 발생할 때 까지 bidding 상태로 holdIn한다
		}
		else if(phaseIs("result")) {	// 모든 bidding round를 마친 후 result 상태가 되면
			end_bidder = max_bidder;	// 최고가를 bidding 한 bidder를 최종 bidder로 set
			end_price = max_price;		// 최종 가격을 최고가로 set
			
			System.out.println(": winner is customer#" + end_bidder + ", result price is " + end_price);
			holdIn("wait", INFINITY);		// internal function의 job을 수행하고 wait 상태로 holdIn
		}
	}

	public message out()
	{
		message m = new message();
		if (phaseIs("start")) 		//start 상태에서 out function
		{
			m.add(makeContent("start", new auction_msg("auction_msg #a(start)", auction.post_price)));		// auction_msg(start) out
		}
		if (phaseIs("sent")) 		//sent 상태에서 out function
		{
			m.add(makeContent("bid_out", new auction_msg("auction_msg #a(sent)", auction.post_price)));		// auction_msg(sent) out
		}
		if (phaseIs("result")) 		//result 상태에서 out function
		{
			m.add(makeContent("result_out", new auction_msg("auction_msg #a(result)", max_price)));			// auction_msg(result) out
		}
		return m;
	}
}

