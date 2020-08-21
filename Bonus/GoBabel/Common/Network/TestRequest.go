package BabelNetwork

//
//type TestDatas struct {
//	Login, Password string
//	Lol uint16
//	Mdr uint8
//}
//
//func NewTestRequest(conn io.ReadWriter, code uint16, login, password string) (*Request, error) {
//	loginSz, passwordSz := uint16(len(login)), uint16(len(password))
//
//	if loginSz > MaxLoginSize || passwordSz > MaxPasswordSize {
//		err := fmt.Sprintf(
//			"login or password too long: %d [%d] <==> %d [%d]",
//			loginSz, MaxLoginSize, passwordSz, MaxPasswordSize,
//		)
//		return nil, errors.New(err)
//	}
//
//	rq := NewRequest(conn)
//	rq.Header.RqType = RqUser
//	rq.Header.Code = code
//	rq.Header.DataInfosSize = uint16(UserInfosSize)
//	rq.Datas = &TestDatas{
//		Login:    login,
//		Password: password,
//	}
//	return rq, nil
//}
//
//func EmptyTestRequest(conn io.ReadWriter) EncodeDecoder {
//	return &TestDatas{}
//}
//
//func (r TestDatas) Encode() []byte {
//
//}
//
//func (r *TestDatas) DecodeInfos(b []byte) {
//	r.LoginSize = binary.LittleEndian.Uint16(b[0:])
//	r.PasswordSize = binary.LittleEndian.Uint16(b[2:])
//}
//
//func (r *TestDatas) DecodeDatas(b []byte) {
//	r.Login = string(b[0:r.LoginSize])
//	r.Password = string(b[r.LoginSize:])
//}
//
//func (r TestDatas) GetSize() uint32 {
//	return uint32(r.LoginSize + r.PasswordSize)
//
//}
