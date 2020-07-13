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


### Connexion (1** Codes )

* Connection
    * 100: Connexion Ok.
    * 199: Connexion Not ok.


### User (\*2** Codes)

* Login (20* Codes)
    * Request / Success Codes.
        * 200: Logged In.
        * 201: Request logging.
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            } 
            ```
        * 202: User Logged In.
        * 203: Request Logged out
            ```json
            {
              "login":      "damien.bernard@epitech.eu"
            } 
            ```
        * 204: User Logged Out.
    * Error Codes    
        * 1200: Unknown login Error.
        * 1201: Wrong Login.
        * 1202: Wrong Password.
        * 1203: Account Deleted.
        * 1204: User Already Logged In.
        * 1205: ??

* Account Creation (\*21* Codes)
    * Request / Success Codes.
        * 210: Request Create Account
            ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            } 
            ```
        * 211: Account Created.
    * Error Codes
        * 1210: Unknown Account Creation Error.
        * 1211: Account Already Taken.
        * 1212: User Already Logged In.
        * 218: Password too weak (??).


* Account Deletion  (22* Codes)
    * Request / Success Codes.
        * 220: Request Delete Account.
        ```json
        {
          "login":      "damien.bernard@epitech.eu"
        } 
        ```
        * 211: Account Deleted.
        

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
    * Data: (None)
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
