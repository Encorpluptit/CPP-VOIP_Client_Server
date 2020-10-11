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
  Response {
    uint16_t _code;
    ResponseType _responseType;
    size_t _dataInfosSize;
  };
  ```

## User (2** Codes)

### Summary

    * 100: User Logged In.
    * 101: Request logging.
    * 102: User Logged Out.
    * 103: Request Logged out.
    * 110: Account Created.
    * 111: Request Create Account.
    * 112: Account Deleted.
    * 113: Request Delete Account.
    * 170: Unknown login Error.
    * 171: Wrong Login.
    * 172: Wrong Password.
    * 173: Login Already Taken.
    * 174: User Already Logged In.
    * 175: Request Account Deleted.
    * 176: Client Logged Out.

    * 200: Call Started.
    * 201: Request Call.
    * 202: Call Left.
    * 203: Request End Call.
    * 204: Incoming Call.
    * 205: Call Accepted.
    * 270: Call Refused.
    * 271: User Disconected.
    * 272: Unknown Error.

    * 300: Request Friendship.
    * 301: Look at this Requested Friendship.
    * 302: ??
    * 303: Requested Friendship was Accepted.
    * 304: Requested Friendship was Decline.
    * 306: Delete this Friend.

    * 350: You are already Friend.
    * 351: Target is not a Friend.
    * 352: User didn't exist.
    * 354: MMmm there is a error. (soz we don't what it is)

### Login (20*|27* Codes)

### Header

im going to specify the header for every responsse for login part
you need to send it to specify the size of the next structure

* _loginSize = size of the login user
* _passwordSize = size of the password user

  ```cpp
  DataInfosStruct {
    uint16_t _loginSize;
    uint16_t _passwordSize;
  };
  ```

### Struct of login responsse

this is the structure for the login responsse fill this struct and send it to server

```cpp
  DataStruct {
    char login[MaxDataSize::Login];
    char password[MaxDataSize::Password];
  };
```

* [Client -> Server]
  * Success Codes.
  * 101: Request logging.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            }
    ```

  * 103: Request Logged out.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * Error Codes

* [Server -> Client]
  * Success Codes.
  * 100: User Logged In.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
      ```

  * 102: User Logged Out.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * Error Codes

  * 170: Unknown login Error.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 171: Wrong Login.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 172: Wrong Password.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 173: Login Already Taken.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 174: User Already Logged In.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 175: Request Account Deleted.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 176: Client Logged Out.

    ```json
            {
            }
    ```

### Account Management (21*|28* Codes)

* [Client -> Server]

  * Success Codes.
  * 111: Request Create Account.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
              "password" :  "abcd1234"
            }
    ```
  
  * 113: Request Delete Account.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * Error Codes

* [Server -> Client]
  * Success Codes.
  * 110: Account Created.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

  * 112: Account Deleted.

    ```json
            {
              "login":      "damien.bernard@epitech.eu",
            }
    ```

---

### Call (3** Codes)

* Re Summary
  * 400: Call started.
  * 401: Request Call.
  * 402: Call Left Successfully.
  * 403: Request End Call.
  * 404: Incoming Call.
  * 405: Call Accepted.

  * 470: Requested Call Refused.
  * 471: Target User is Disconnected.
  * 472: Unknown Error.

### Header

im going to specify the header for every responsse for Call part 
you need to send it to specify the size of the next structure

* _senderSize = size of the login user
* _receiverSize = size of the login user
* _timestampSize = size of the timeStamp
* _ipSize = size of the ip user
* _portSize = size of the por user

  ```cpp
    DataInfosStruct {
      uint16_t _senderSize;
      uint16_t _receiverSize;
      uint8_t _timestampSize;
      uint8_t _callIdSize;
      uint8_t _ipSize;
      uint8_t _portSize;
    };
  ```

### Struct of call responsse

this is the structure for the Call responsse fill this struct and send it to server

```cpp
  DataStruct {
    char sender[MaxDataSize::Sender];
    char receiver[MaxDataSize::Receiver];
    time_t timestamp;
    uint16_t callId;
    char ip[MaxDataSize::Sender];
    char port[MaxDataSize::Receiver];
  };
```

* Call Status
  * [Server -> Client]
  * Success Codes.
    * 400: Call Started.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "callId":             "ConvId",
                "ip":                 "damienIP",
                "port":               "damienPort",
              }
      ```

    * 402: Call Left Successfully.

      ```json
              {
                "sender":             "ugo.levi-cescutti@epitech.eu",
                "receiver":           "damien.bernard@epitech.eu",
              }
      ```

    * 404: Incoming Call.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "ip":                 "DamienIP",
                "port":               "damien port",
              }
      ```

    * Error Codes
    * 470: Requested Call Refused.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "callId":             "ConvId",
                "ip":                 "damienIP",
                "port":               "damienPort",
              }
      ```

    * 471: Target is Disconnected.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
              }
      ```

    * [Client -> Server]

    * Success Codes.
    * 401: Request Start Call.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "callId":             "ConvId",
                "ip":                 "damienIp",
                "port":               "damienPort",
              }
      ```

    * 403: Request End Call.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "callId":             "ConvId",
                "ip":                 "UgoIP",
                "port":               "UgoPort",
              }
      ```

    * 405: Call Accepted.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu",
                "timestamp":          "(unix time)",
                "callId":             "ConvId",
                "ip":                 "UgoIP",
                "port":               "UgoPort",
              }
      ```

    * Error Codes

<!-- * Conference(21* Codes) -->

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
  * 300: Request Friendship.
  * 301: Look at this Requested Friendship.
  * 302: ??
  * 303: Requested Friendship was Accepted.
  * 304: Requested Friendship was Decline.
  * 306: Delete this Friend.

  * 350: You are already Friend.
  * 351: Target is not a Friend.
  * 352: User didn't exist.
  * 354: MMmm there is a error. (soz we don't what it is)

### Header

im going to specify the header for every responsse for Friend part
you need to send it to specify the size of the next structure

* _loginSize = size of the login user
* _friendLoginSize = size of the login user

  ```cpp
  DataInfosStruct {
    uint16_t _loginSize;
    uint16_t _friendLoginSize;
  };
  ```

### Struct of call responsse

this is the structure for the Call responsse fill this struct and send it to server

  ```cpp
    DataStruct {
      char login[MaxDataSize::Login];
      char FriendLogin[MaxDataSize::FriendLogin];
    };
  ```

* Friend Management
  * [Client -> Server]
    * Success Codes.
    * 300: Request Friendship.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

    * 306: Delete this Friend.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

  * [Server -> Client]
    * Success Codes.

    * 303: Requested Friendship was Accepted.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

    * 304: Requested Friendship was Decline.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

    * 301: Look at this Requested Friendship.
  
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

    * 350: You are already Friend.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

    * 352: User didn't exist.

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```

    * 354: MMmm there is a error. (soz we don't what it is)

      ```json
              {
                "sender":             "damien.bernard@epitech.eu",
                "receiver":           "ugo.levi-cescutti@epitech.eu"
              }
      ```
