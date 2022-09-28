#pragma once

const char GP_2_LIGHT[] PROGMEM =
"<style type=\"text/css\">\n"
".scroll_box {height:500px;border-radius:10px;background-color:#f2f2f2;padding:15px 0px;margin:30 30px;width:90%;overflow:auto;}\n"
".button_select {border-radius:8px;padding:3px 10px;font-size:24px;height:40px;width:90%;margin:8px 5px;background-color:#bababa;border:none;color:#bbb;cursor:pointer;}\n"

".upload_button_label {font-size:28px;padding: 14px 12px;background-color:#1300e3;border:none;border-radius:8px;color:white;cursor:pointer;}\n"
".upload_button_button {width: 0.1px; height: 0.1px; opacity: 0; overflow: hidden; position: absolute; z-index: -1;}\n"

"</style>\n";

const char GP_2_DARK[] PROGMEM =
"<style type=\"text/css\">\n"
".scroll_box {height:500px;border-radius:10px;background-color:#2a2d35;padding:15px 0px;margin:30 30px;width:90%;overflow:auto;}\n"
".button_select {border-radius:10px;padding:5px 10px;font-size:24px;height:auto;width:90%;margin:8px 5px;background-color:#24272e;border:none;color:#bbb;cursor:pointer;}\n"

".upload_button_label {font-size:28px;padding: 14px 12px;background-color:#1300e3;border:none;border-radius:8px;color:white;cursor:pointer;}\n"
".upload_button_button {width: 0.1px; height: 0.1px; opacity: 0; overflow: hidden; position: absolute; z-index: -1;}\n"

"</style>\n";

struct BuilderAddon {
	//https://base64.guru/converter/encode/image/ico
	void BUILD_BEGIN_FAVICON_BASE64(const String& page_name = "ESP", const String& faviconBase64 = "", uint16_t width = 350, bool local = false) {
		PAGE_BEGIN_FAVICON_BASE64(page_name, faviconBase64);
		if (local) GP.JS_TOP_FILE();
		else GP.JS_TOP();
		GP.PAGE_BLOCK_BEGIN(width);
	}
	
	void PAGE_BEGIN_FAVICON_BASE64(const String& page_name, const String& faviconBase64) {
		String href;
		if (faviconBase64.length()) { 
			href += F("data:image/x-icon;base64,");
			href += faviconBase64;
		}
		PAGE_BEGIN_FAVICON_HREF(page_name, href);
	}
	
	
	void BUILD_BEGIN_FAVICON_HREF(const String& page_name = "ESP", const String& href = "", uint16_t width = 350, bool local = false) {
		PAGE_BEGIN_FAVICON_HREF(page_name, href);
		if (local) GP.JS_TOP_FILE();
		else GP.JS_TOP();
		GP.PAGE_BLOCK_BEGIN(width);
	}
	
	void PAGE_BEGIN_FAVICON_HREF(const String& page_name, const String& href) {
		String s;
		s += F("<!DOCTYPE HTML><html><head>\n"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
		"<meta charset=\"utf-8\">\n");
		s += F("<title>");
		s += page_name;
		s += F("</title>\n");
		if (href.length()) { 
			s += F("<link rel=\"shortcut icon\" href=\"");
			s += href;
			s += F("\">");
		}
		s += F("</head><body>\n");
		GP.SEND(s);
	}
	
	void BUILD_BEGIN(const String& page_name = "ESP", uint16_t width = 350, bool local = false) {
		PAGE_BEGIN(page_name);
		if (local) GP.JS_TOP_FILE();
		else GP.JS_TOP();
		GP.PAGE_BLOCK_BEGIN(width);
	}
	
	void PAGE_BEGIN(const String& page_name) {
		String s;
		s += F("<!DOCTYPE HTML><html><head>\n"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
		"<meta charset=\"utf-8\">\n");
		s += F("<title>");
		s += page_name;
		s += F("</title>\n");
		s += F("</head><body>\n");	
		GP.SEND(s);
	}
	
	void OPEN_WEB_PAGE(const String& href,int prd = 1000) {
		String s;
		s += F("<script> setInterval(function(){window.location.href = \"");
		s += href;
		s += F("\";},");
		s += prd;
		s += F(");</script>\n");
		GP.SEND(s);
	}
	
	void SCROLL_BOX() {
		String s;
		s += F("<div class='scroll_box' id='blockBack'>\n");
		GP.SEND(s);
	}
	
	void UPDATE_SLIDER(const String& list, int prd = 1000) {
        String s;
        s.reserve(500);
        s += F("<script>setInterval(function(){\n");
        s += "var ids='";
        s += list;
        s += F("'.split(',');\n"
        "ids.forEach(function(id){\n"
        "var xhttp=new XMLHttpRequest();\n"
        "xhttp.onreadystatechange=function(){\n"
        "if(this.readyState==4&&this.status==200){\n"
        "var resp=this.responseText;\n"
		"var variable = id.split('.');\n"
        "var item=document.getElementById(variable[0]);if(item==null || item.type !='range')return;\n"
		"if (variable[1] =='min')item.min = resp;\n"
		"else if (variable[1] =='max')item.max = resp;\n"
		"else if (variable[1] =='step')item.step = resp;\n"
		"else item.value=resp;\n"
		"GP_change(item);\n"
        "}};xhttp.open('GET','/GP_update?'+id+'=',true);xhttp.send();});},");
        s += prd;
        s += F(");</script>\n");
        GP.SEND(s);
    }
	
	void BOX_SELECT_LINK_BEGIN(const String& url = "") {
		String s;
		s += F("<div class=\"button_select\" ");
		s += F(" onclick=\"{const div = this.parentElement.children;");
		s += F("for (let i = 0; i<div.length; i++) {if (div[i].className == 'button_select') { div[i].style.backgroundColor = '#24272e';}}");
		s += F("this.style.backgroundColor = '#3c414d';");
		
		s += F("this.children[0].click();");
		
		s += F("}\"><button style='height: 0px;width: 90%;' ");
		s += F("onclick='location.href=\"");
		s += url;
		s += F("\"'></button><div style=\"justify-content:space-between;display:flex;align-items: center;\">\n");
		
		GP.SEND(s);
	}
	
	void BOX_SELECT_BEGIN(const String& name = "") {
		String s;
		s += F("<div class=\"button_select\" name=\"");
		s += name;
		s += F("\" onclick=\"{const div = this.parentElement.children;");
		s += F("for (let i = 0; i<div.length; i++) {if (div[i].className == 'button_select') { div[i].style.backgroundColor = '#24272e';}}");
		s += F("this.style.backgroundColor = '#3c414d';");
		
		s += F("this.children[0].click();");
		
		s += F("}\"><button style='height: 0px;width: 90%;' name='");
		s += name;
		s += F("' onclick='GP_click(this)'></button><div style=\"justify-content:space-between;display:flex;align-items: center;\">\n");
		
		GP.SEND(s);
	}
	
	void BOX_SELECT_END() {
		String s;
		s += F("</div></div>\n");
		GP.SEND(s);
	}
	
	void BUTTON_SELECT(const String& name, const String& value) {
		String s;
		s += F("<button class=\"button_select\" name=\"");
		s += name;
		s += F("\" onclick=\"{const div = this.parentElement.children;");
		s += F("for (let i = 0; i<div.length; i++) {if (div[i].className == 'button_select') { div[i].style.backgroundColor = '#24272e';}}");
		s += F("this.style.backgroundColor = '#3c414d';");
		
		s += F("GP_click(this)");
		
		s += F("}\">");
		
		s += value;
		
		s += F("</button>\n");
		GP.SEND(s);
	}
	
	void SUBMIT_MINI(const String& text, PGM_P st= GP_GREEN) {
		GP.SUBMIT(text + F("' class='miniButton"), st);
    }
	
	void UPLOAD_BUTTON(const String& name, const String& value, const String& value_submit ,const String& label_id="" , const String& accept="") {
		String s;
		s += F("<form action='/GP_upload' method='POST'> <div>");
		
		s += F("<br>\n");
		
		s += F("<label class=\"upload_button_label\" id=\"");
		s += label_id;
		s += F("\" for=\"");
		s += name;
		s += F("\">");
		s += value;
		s += F("</label>\n");
		
		s += F("<input type=\"file\" class=\"upload_button_button\" name=\"");
		s += name;
		s += F("\" id=\"");
		s += name;
		s += F("\" accept=\"");
		s += accept;
		s += F("\" onclick=\"GP_click(this)\" onchange=\"this.parentElement.children[6].innerHTML = this.files[0].name\">\n");
		
		s += F("<br>\n");
		s += F("<br>\n");
		s += F("<br>\n");
		
		s += F("<label></label>");
		
		s += F("</div>");
		
		s += F("<br>");
		
		s += F("<input type=\"submit\" formenctype=\"multipart/form-data\" value=\"");
		s += value_submit;
		s += F("\"> </form>\n");
		GP.SEND(s);
	}
	
	void HREF_BEGIN(const String& GP_href) {
		String s;
		s += F("<a class=\"\" style=\"text-decoration: none;\" href=\"");
		s += GP_href;
		s += F("\">\n");
		GP.SEND(s);
	}
	
	void HREF_END() {
		String s;
		s += F("</a>\n");
		GP.SEND(s);
	}
	
	void HREF(const String& GP_href) {
		String s;
		s += F("<a class=\"\" href=\"");
		s += GP_href;
		s += F("\">\n");
		s += F("</a>");
		GP.SEND(s);
	}
	
	void TEXT_HREF(const String& name, const String& value, const String& GP_href) {
		String s;
		s += F("<a href=\"");
		s += GP_href;
		s += F("\" name=\"");
		s += name;
		s += F("\" onclick=\"GP_click(this)\">\n");
		s += value;
		s += F("</a>");
		GP.SEND(s);
	}
};
BuilderAddon GP_2;