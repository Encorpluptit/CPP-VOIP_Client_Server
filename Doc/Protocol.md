# Babel Protocol
Full documentation of server/client protocol.


   ![alt text][logo]

   [logo]: ./UML.png "UML diagram image in Doc Folder"


---
## Syntax:
* `event`
    * `Description`
    * `[ CODE SUCESS | CODE ERROR | DATA ]`

## Events


### User (2** Codes)
* Summary
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
    * 273: Account Deleted.
    * 274: User Already Logged In.
    * 280: Unknown Account Creation Error.
    * 281: Account Already Taken.
    * 282: User Already Logged In.
    

* Login
    * [Server -> Client]
        * Success Codes.
            * 200: User Logged In.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 202: User Logged Out.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
        * Error Codes    
            * 270: Unknown login Error.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 271: Wrong Login.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 272: Wrong Password.
            * 273: Account Deleted.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 274: User Already Logged In. (???)
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
    * [Client -> Server]
        * 201: Request logging.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            }
            ```
        * 203: Request Logged out.
            ```json
            {
              "login":      "damien.bernard@epitech.eu"
            } 
            ```
        * 275: ??

* Account (21* Codes)
    * [Server -> Client]
        * Success Codes.
            * 210: Account Created.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 212: Account Deleted.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
        * Error Codes
            * 280: Unknown Account Creation Error.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 281: Account Already Taken.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 282: User Already Logged In.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 218: Password too weak. (??)
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
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
        

### Call (3** Codes)
* Summary
    * 300: Requested Call started.
    * 301: Request Start Call.
    
    * 370: Requested Call Refused.
    

* Login
    * [Server -> Client]
        * Success Codes.
            * 300: Requested Call started.
                ```json
                {
                  "login":              "damien.bernard@epitech.eu",
                  "timestamp":          "(unix time)",
                  "ConferenceId":       "1"
                }
                ```
            * 202: User Logged Out.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
        * Error Codes    
            * 270: Unknown login Error.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 271: Wrong Login.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 272: Wrong Password.
            * 273: Account Deleted.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 274: User Already Logged In. (???)
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
    * [Client -> Server]
        * 201: Request logging.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            }
            ```
        * 203: Request Logged out.
            ```json
            {
              "login":      "damien.bernard@epitech.eu"
            } 
            ```
        * 275: ??

* Account (21* Codes)
    * [Server -> Client]
        * Success Codes.
            * 210: Account Created.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 212: Account Deleted.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
        * Error Codes
            * 280: Unknown Account Creation Error.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 281: Account Already Taken.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 282: User Already Logged In.
                ```json
                {
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```
            * 218: Password too weak. (??)
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
                  "login":      "damien.bernard@epitech.eu"
                } 
                ```

```
* Add a friend.
    * Delete an account.
    * Success code: 230
    * Data: (None)
    * Errors:
        * 1230: Unknown Account deletion error.
        * 1231: Account logged somewhere else.
```

### Call (3** Code)

* Start a call (31* Code).
    * Calling someone.
    * Success code: 310
    * Data:  [ USERNAME ]
    * Errors:
        * 1310: Unknown Call starting error.
        * 1311: Call Refused.
        * 1312: Call timeout.
        * 1313: User not logged in.


* Incoming Call (32* Code).
    * Someone is calling you.
    * Success code: 320
    * Data: [ USERNAME | TIMESTAMP | CONFERENCE_ID ]
    * Errors:
        * 1320: Unknown incoming error.
        * 1321: Call timeout.


* Accept Call (33* Code).
    * Accept call.
    * Success code: 330
    * Data: (None)
    * Errors:
        * 1330: Unknown accept call error.
        * 1331: Unknown accept call error.


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


### Messages (5** Codes )

* Connection OK
    * Client is connected to server.
    * 



## Errors (1*** Codes)

* Unknown Error
    * An unknown error occurred.
    * code: 1000.
