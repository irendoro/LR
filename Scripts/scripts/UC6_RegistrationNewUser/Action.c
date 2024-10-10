Action()
{

	lr_start_transaction("UC6_RegistrationNewUser");

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

	lr_think_time(6);

	lr_start_transaction("Go_to_SignUp");
	
	web_reg_find("Text=First time registering? Please complete the form below.",LAST);

	web_url("login.pl", 
		"URL=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Resource=0", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/WebTours/home.html", 
		"Snapshot=t2.inf", 
		"Mode=HTML", 
		LAST);

	lr_end_transaction("Go_to_SignUp",LR_AUTO);

	lr_start_transaction("User_SignUp");
	
	web_reg_find("Text=Thank you, <b>{username}</b>, for registering and welcome to the Web Tours family.",LAST);

	web_add_auto_header("Upgrade-Insecure-Requests", 
		"1");

	lr_think_time(10);

	web_submit_data("login.pl_2", 
		"Action=http://localhost:1080/cgi-bin/login.pl", 
		"Method=POST", 
		"RecContentType=text/html", 
		"Referer=http://localhost:1080/cgi-bin/login.pl?username=&password=&getInfo=true", 
		"Snapshot=t3.inf", 
		"Mode=HTML", 
		ITEMDATA, 
		"Name=username", "Value={username}", ENDITEM, 
		"Name=password", "Value={password}", ENDITEM, 
		"Name=passwordConfirm", "Value={password}", ENDITEM, 
		"Name=firstName", "Value={firstName}", ENDITEM, 
		"Name=lastName", "Value={lastName}", ENDITEM, 
		"Name=address1", "Value={address1}", ENDITEM, 
		"Name=address2", "Value={address2}", ENDITEM, 
		"Name=register.x", "Value=44", ENDITEM, 
		"Name=register.y", "Value=6", ENDITEM, 
		LAST);

	lr_end_transaction("User_SignUp",LR_AUTO);

	lr_think_time(9);
	
	lr_start_transaction("Login");
	
	web_reg_find("Text=Welcome, <b>{username}</b>, to the Web Tours reservation pages.",LAST);
	
	web_image("button_next.gif", 
		"Src=/WebTours/images/button_next.gif", 
		"Snapshot=t4.inf", 
		LAST);

	lr_end_transaction("Login",LR_AUTO);
	
	lr_think_time(9);

	lr_start_transaction("Logout");
	
	web_reg_find("Text=Welcome to the Web Tours site.",LAST);

	web_image("SignOff Button", 
		"Alt=SignOff Button", 
		"Snapshot=t5.inf", 
		LAST);

	lr_end_transaction("Logout",LR_AUTO);

	lr_end_transaction("UC6_RegistrationNewUser",LR_AUTO);

	return 0;
}