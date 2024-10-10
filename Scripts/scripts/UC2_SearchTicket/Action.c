Action()
{
	lr_start_transaction("UC2_SearchTicket");
	
	lr_start_transaction("Go_to_Web_tours");

	web_reg_find("Text=Welcome to the Web Tours site.",LAST);
	
	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");
	
	web_url("welcome.pl", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/", 
		"Snapshot=t1.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Go_to_Web_tours",LR_AUTO);

	lr_start_transaction("Login");
	
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("Login",LR_AUTO);

	lr_start_transaction("Go_To_Flights");
	
	web_reg_save_param_ex("ParamName=City","LB=option value=\"","RB=\"","Ordinal=ALL",LAST);

	web_reg_find("Text=\<td align\=\"left\"\>Departure City :\</td> \<td\>\<select name\=\"depart\" \>",LAST);
	
	web_image("Search Flights Button", 
		"Alt=Search Flights Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("Go_To_Flights",LR_AUTO);

	lr_start_transaction("Find_Flight");
	
	lr_save_string(lr_paramarr_random("City"),"DepartureCity");
	do {
    	lr_save_string(lr_paramarr_random("City"),"ArrivalCity");
	} while (strcmp(lr_eval_string("{DepartureCity}"), lr_eval_string("{ArrivalCity}")) == 0);
	
	web_reg_find("Text=Flight departing from <B>{DepartureCity}</B> to <B>{ArrivalCity}</B> on <B>{departDate}</B>",LAST);
	
	web_submit_data("reservations.pl", 
		"Action=http://localhost:1080/cgi-bin/reservations.pl", 
		"Method=POST", 
		"TargetFrame=", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/reservations.pl?page=welcome", 
		"Snapshot=t4.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=depart", "Value={DepartureCity}", ENDITEM, 
		"Name=departDate", "Value={departDate}", ENDITEM, 
		"Name=arrive", "Value={ArrivalCity}", ENDITEM, 
		"Name=returnDate", "Value={returnDate}", ENDITEM, 
		"Name=numPassengers", "Value=1", ENDITEM, 
		"Name=seatPref", "Value={seatPref}", ENDITEM, 
		"Name=seatType", "Value={seatType}", ENDITEM, 
		"Name=findFlights.x", "Value=75", ENDITEM, 
		"Name=findFlights.y", "Value=13", ENDITEM, 
		LAST);

	lr_end_transaction("Find_Flight",LR_AUTO);

	lr_start_transaction("Logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_url("SignOff Button", 
		"URL=http://localhost:1080/cgi-bin/welcome.pl?signOff=1", 
		"TargetFrame=body", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/nav.pl?page=menu&in=home", 
		"Snapshot=t5.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);
	
	lr_end_transaction("UC2_SearchTicket",LR_AUTO);

	return 0;
}