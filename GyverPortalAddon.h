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
".button_select {border-radius:8px;padding:3px 10px;font-size:24px;height:40px;width:90%;margin:8px 5px;background-color:#24272e;border:none;color:#bbb;cursor:pointer;}\n"

".upload_button_label {font-size:28px;padding: 14px 12px;background-color:#1300e3;border:none;border-radius:8px;color:white;cursor:pointer;}\n"
".upload_button_button {width: 0.1px; height: 0.1px; opacity: 0; overflow: hidden; position: absolute; z-index: -1;}\n"

"</style>\n";

struct BuilderAddon {
	//https://base64.guru/converter/encode/image/ico
	void BUILD_BEGIN_FAVICON_BASE64(const char* page_name = "ESP", const char* faviconBase64 = "") {
		PAGE_BEGIN_FAVICON_BASE64(page_name, faviconBase64);
		GP.AJAX_CLICK();
		GP.PAGE_BLOCK_BEGIN();
	}
	
	void PAGE_BEGIN_FAVICON_BASE64(const char* page_name, const char* faviconBase64) {
		String href;
		if (faviconBase64) { 
			href += F("data:image/x-icon;base64,");
			href += faviconBase64;
		}
		PAGE_BEGIN_FAVICON_HREF(page_name, href.c_str());
	}
	
	
	void BUILD_BEGIN_FAVICON_HREF(const char* page_name = "ESP", const char* href = "") {
		PAGE_BEGIN_FAVICON_HREF(page_name, href);
		GP.AJAX_CLICK();
		GP.PAGE_BLOCK_BEGIN();
	}
	
	void PAGE_BEGIN_FAVICON_HREF(const char* page_name, const char* href) {
		*_GP += F("<!DOCTYPE HTML><html><head>\n"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
		"<meta charset=\"utf-8\">\n");
		*_GP += F("<title>");
		*_GP += page_name;
		*_GP += F("</title>\n");
		if (href) { 
			*_GP += F("<link rel=\"shortcut icon\" href=\"");
			*_GP += href;
			*_GP += F("\">");
		}
		*_GP += F("</head><body>\n");	
	}
	
	
	
	void BUILD_BEGIN(const char* page_name = "ESP") {
		PAGE_BEGIN(page_name);
		GP.AJAX_CLICK();
		GP.PAGE_BLOCK_BEGIN();
	}
	
	void PAGE_BEGIN(const char* page_name) {
		*_GP += F("<!DOCTYPE HTML><html><head>\n"
		"<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
		"<meta charset=\"utf-8\">\n");
		*_GP += F("<title>");
		*_GP += page_name;
		*_GP += F("</title>\n");
		*_GP += F("</head><body>\n");	
	}
	
	void OPEN_WEB_PAGE(const char* href,int prd = 1000) {
		*_GP += F("<script> setInterval(function(){window.location.href = \"");
		*_GP += href;
		*_GP += F("\";},");
		*_GP += prd;
		*_GP += F(");</script>\n");
	}
	
	void SCROLL_BOX() {
		*_GP += F("<div class=\"scroll_box\" id=\"blockBack\">\n");
	}
	
	void BUTTON_SELECT(const char* name, const char* value) {
		*_GP += F("<button class=\"button_select\" name=\"");
		*_GP += name;
		*_GP += F("\" onclick=\"{const div = this.parentElement.children;");
		*_GP += F("for (let i = 0; i<div.length; i++) {if (div[i].className == 'button_select') { div[i].style.backgroundColor = '#24272e';}");
		*_GP += F("this.style.backgroundColor = '#3c414d';");
		
		*_GP += F("GP_click(this)");
		
		*_GP += F("}}\">");
		
		*_GP += value;
		
		*_GP += F("</button>\n");
		
	}
	
	void UPLOAD_BUTTON(const char* name, const char* value, const char* value_submit ,const char* label_id="" , const char* accept="") {
		*_GP += F("<div>");
		
		*_GP += F("<br>\n");
		
		*_GP += F("<label class=\"upload_button_label\" id=\"");
		*_GP += label_id;
		*_GP += F("\" for=\"");
		*_GP += name;
		*_GP += F("\">");
		*_GP += value;
		*_GP += F("</label>\n");
		
		*_GP += F("<input type=\"file\" class=\"upload_button_button\" name=\"");
		*_GP += name;
		*_GP += F("\" id=\"");
		*_GP += name;
		*_GP += F("\" accept=\"");
		*_GP += accept;
		*_GP += F("\" onclick=\"GP_click(this)\" onchange=\"this.parentElement.children[6].innerHTML = this.files[0].name\">\n");
		
		*_GP += F("<br>\n");
		*_GP += F("<br>\n");
		*_GP += F("<br>\n");
		
		*_GP += F("<label></label>");
		
		*_GP += F("</div>");
		
		*_GP += F("<br>");
		
		*_GP += F("<input type=\"submit\" formenctype=\"multipart/form-data\" value=\"");
		*_GP += value_submit;
		*_GP += F("\">\n");
	}
	
	void HREF_BEGIN(const char* GP_href) {
		*_GP += F("<a class=\"\" href=\"");
		*_GP += GP_href;
		*_GP += F("\">\n");
	}
	
	void HREF_END() {
		*_GP += F("</a>\n");
	}
	
	void HREF(const char* GP_href) {
		*_GP += F("<a class=\"\" href=\"");
		*_GP += GP_href;
		*_GP += F("\">\n");
		*_GP += F("</a>");
	}
	
	void TEXT_HREF(const char* name, const char* value, const char* GP_href) {
		*_GP += F("<a href=\"");
		*_GP += GP_href;
		*_GP += F("\" name=\"");
		*_GP += name;
		*_GP += F("\" onclick=\"GP_click(this)\">\n");
		*_GP += value;
		*_GP += F("</a>");
	}
};
BuilderAddon GP_2;