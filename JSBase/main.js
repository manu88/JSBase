

//var runLoop = new RunLoop();

function Object()
{
	this.foo  = 42;
	this.realCall = function()
	{
	print("Hello Object " + this.foo + "\n");
	};
	this.testCall = function()
	{
		this.realCall();	
	};
}


var a = new Object();


runLoop.async( a.testCall() );



function clb()
{
	print("Async 1 ok \n");
	runLoop.async( function()
		{
			print("Async 2 ok \n") ;
			//runLoop.stop();
		} ) ;
}
function main()
{
	runLoop.after( 2000 , clb ) ;
	print("RunLoop running\n");
	
	var t1 = new Timer();
	t1.interval = 500 ;
	
	t1.callback = function()
	{
		 print("On time 1 : "+ t1.interval + "\n"); 
	};
	print("1 :Interval  : " + t1.interval + " active : "+ t1.active +"\n");
	runLoop.addTimer(t1);

	var t2 = new Timer();
	t2.interval = 1000;
	t2.callback = function(){ print("On time 2 : "+ t2.interval + "\n"); };
	print("2 : Interval  : " + t2.interval + " active : "+ t2.active +"\n");
	runLoop.addTimer(t2);
	
	var inp = new InSource( 0 ); // stdin
	inp.onRead = function(datas)
	{
		print("Read :'" + datas + "'");
		if( datas == "stop")
		{
			runLoop.stop();
		}
	};
	runLoop.addSource(inp);
	runLoop.run();

	print("RunLoop returned \n");
	
}

//main();