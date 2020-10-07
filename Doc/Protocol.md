# Babel Protocol
Full documentation of server/client protocol.


   ![alt text][logo]

   [logo]: ./BabelClasses.png "UML diagram image in Doc Folder"


---
## AResponse
that is the classic header for a responsse

  * _code = responsse code
  * ResponseType = the struct type of response 
  * _datainfosSize = size of the next structure

  ```cpp
  struct __attribute__((packed)) Response {
    uint16_t _code;
    ResponseType _responseType;
    size_t _dataInfosSize;
  };
  ```

## User (2** Codes)
### Summary

    * 200: User Logged In.
    * 201: Request logging.
    * 202: User Logged Out.
    * 203: Request Logged out.
    * 210: Account Created.
    * 211: Request Create Account.
    * 212: Account Deleted.
    * 213: Request Delete Account.
    
    * 270: Unknown login Error.
    * 271: Wrong Login.
    * 272: Wrong Password.
    * 273: Requested Account Deleted.
    * 274: User Already Logged In.
    * 280: Login Already Taken.
    * 281: User Already Logged In.


### Login (20*|27* Codes)

* [Client -> Server]
    * Success Codes.
        * 201: Request logging.
            ```json
            auto {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            }
            ```
        * 203: Request Logged out.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 275: ??
    * Error Codes

* [Server -> Client]
    * Success Codes.
        * 200: User Logged In.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 202: User Logged Out.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
    * Error Codes    
        * 270: Unknown login Error.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 271: Wrong Login.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 272: Wrong Password.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 273: Account Deleted.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 274: User Already Logged In. (???)
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```

### Account Management (21*|28* Codes)

* [Client -> Server]
    * Success Codes.
        * 211: Request Create Account.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            } 
            ```
        * 213: Request Delete Account.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
    * Error Codes

* [Server -> Client]
    * Success Codes.
        * 210: Account Created.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 212: Account Deleted.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
    * Error Codes
        * 280: Login Already Taken.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 281: User Already Logged In (??).
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  ""
            } 
            ```
        * 282: Password too weak. (??)
        
---

### Call (3** Codes)
* Summary
    * 300: Call started.
    * 301: Request Call.
    * 302: Call Left Successfully.
    * 303: Request End Call.
    * 304: Incoming Call.
    * 305: Call Accepted.
    
    * 370: Requested Call Refused.
    * 371: Target is Disconnected.
    

* Call Status
    * [Server -> Client]
        * Success Codes.
            * 300: Requested Call started.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       "1"
                }
                ```
            * 302: Call Left Successfully.
                ```json
                {
                  "sender":             "ugo.levi-cescutti@epitech.eu",
                  "receiver":           "",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       "1"
                }
                ```
            * 304: Incoming Call.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       "1"
                }
                ```
        * Error Codes
            * 370: Requested Call Refused.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       ""
                }
                ```
            * 371: Target is Disconnected.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       ""
                }
                ```
    * [Client -> Server]
        * Success Codes.
            * 301: Request Start Call.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       ""
                }
                ```
            * 303: Request End Call.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "",
                  "timestamp":          "",
                  "ConferenceId":       "1"
                }
                ```
            * 305: Call Accepted.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       "1"
                }
                ```
        * Error Codes

* Conference(21* Codes)

<!--
        * Add user to conference (34* Code).
            * Add someone to ongoing conference.
            * Success code: 340.
            * Data: (None).
            * Errors:
                * 1340: Unknown add to conference error.
                * 1341: Unknown add to conference error.
        
        
        * Remove user from conference (35* Code).
            * Remove someone to ongoing conference.
            * Success code: 350.
            * Data: [ USERNAME | TIMESTAMP | CONFERENCE_ID ]
            * Errors:
                * 1350: Unknown remove from conference error.
                * 1351: Unknown remove from conference error.

-->

---

### Friend (4** Code)
* Summary
    * 400: Request Friendship.
    * 401: Accept Requested Friendship.
    * 402: Accept Requested Friendship.
    * 403: New Friendship.
    * 404: Friendship.
    
    * 470: Target is not a Friend.
    * 471: Requested Friendship Refused.

* Friend Management
    * [Client -> Server]
        * Success Codes.
            * 400: Request Friendship.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```
            * 403: New Friendship.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```
            * 410: Refuse Requested Friendship.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```
            * 406: Delete Friend Request.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```
        * Error Codes
    * [Server -> Client]
        * Success Codes.
            * 406: Request Friendship.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```
        * Error Codes
            * 471: Requested Friendship refused.
                ```json
                {
                  "sender":             "damien.bernard@epitech.eu",
                  "receiver":           "ugo.levi-cescutti@epitech.eu"
                }
                ```

* Friend Status
    * [Server -> Client]
        * Success Codes.
        * Error Codes


### Messages (5** Codes )
