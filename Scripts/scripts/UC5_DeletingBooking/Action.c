Action()
{
	int i;
	lr_start_transaction("UC5_DeletingBooking");

	lr_start_transaction("Go_to_WebTours");
	
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

	lr_end_transaction("Go_to_WebTours",LR_AUTO);

	lr_think_time(8);

	lr_start_transaction("Login");
	
	web_reg_find("Text=Welcome, <b>{login}</b>, to the Web Tours reservation pages.",LAST);

	web_submit_form("login.pl", 
		"Snapshot=t2.inf", 
		ITEMDATA, 
		"Name=username", "Value={login}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		LAST);

	lr_end_transaction("Login",LR_AUTO);

	lr_think_time(11);

	lr_start_transaction("Go_to_Itenarary");

	web_image("Itinerary Button", 
		"Alt=Itinerary Button", 
		"Snapshot=t3.inf", 
		LAST);

	lr_end_transaction("Go_to_Itenarary",LR_AUTO);

	lr_think_time(13);

	lr_start_transaction("Delete_booking");
	
	lr_save_string("", "c_buffer");

    for (i=1;i<=atoi(lr_eval_string("{c_flightids_count}"));i++)
    {
    	lr_save_string(lr_paramarr_random("c_cgifields"),"c_rand");

		lr_param_sprintf("c_buffer", "%s%d=on&", lr_eval_string("{c_buffer}"), atoi(lr_eval_string("{c_rand}")));
        lr_param_sprintf("c_buffer","%sflightID=%s&",lr_eval_string("{c_buffer}"),lr_paramarr_idx("c_flightids",i));

        lr_param_sprintf("c_buffer","%s.cgifields=%s&",lr_eval_string("{c_buffer}"),lr_paramarr_idx("c_cgifields",i));
    }

    lr_save_string(lr_eval_string("{c_buffer}removeFlights.x=57&removeFlights.y=10&"), "c_wcr");

    lr_save_string(lr_eval_string(lr_eval_string("{c_flightids_{c_flightids_count}}")),"c_cancelflight");

    web_reg_find("Text={c_cancelflight}", "Fail=Found", LAST);

	web_custom_request("itinerary.pl_2",
	    "URL=http://localhost:1080/cgi-bin/itinerary.pl",
	    "Method=POST",
	    "Resource=0",
	    "RecContentType=text/html",
	    "Referer=http://localhost:1080/cgi-bin/itinerary.pl",
	    "Snapshot=t4.inf",
	    "Mode=HTTP",
	    "Body={c_wcr}",
    LAST);

	lr_end_transaction("Delete_booking",LR_AUTO);

	lr_think_time(8);

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

	lr_end_transaction("UC5_DeletingBooking",LR_AUTO);

	return 0;
}