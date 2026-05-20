**drone_webrtc.py** - Contains the WebRTC code      
**index.html** - Contains the website code      

## **To access the WebRTC**
1. Plug in power to the Jetson (Duh!)
2. Wait for about a minute to let the jetson boot up
3. On your computer, open wifi settings and connect to the Jetson's Hotspot
4. Password:      
     Team8Rox      
6. Once connected, open chrome then go to:      
    chrome://flags      
7. Find "Anonymize local IPs exposed by WebRTC" and "Insecure origins treated as secure"
8. Under the "Insecure origins treated as secure", place this URL:      
     http://172.20.10.6
   Not gonna lie, not sure if this is actual url (I wrote this after I graduated)      
   You're gonna have to check it yourself in the wifi IP address settings thing or in the Command prompt using the "hostname -I" command (i think)
10. Open a new tab, then go the URL/IP above to access the Jetson's WebRTC
11. Click the "Connect" button, wait a few seconds then BOOM SHAKALAKA!
12. You're welcome bro






## **To access the Jetson**
1. Connect Jetson via USB-C
2. Open Command Prompt
3. Type this command:
   ssh f2024-team5@192.168.55.1
4. Will ask for password and it wont show what you've typed so be careful. Password:
   Team5Rox
5. Once it changes to "f2024-team5@f2024team5-desktop:~$" then you're in!
6. Below are our codes. Figure out how to edit these:      
**drone_webrtc.py** - Contains the WebRTC code      
**index.html** - Contains the website code      




Anyway, goodluck!
