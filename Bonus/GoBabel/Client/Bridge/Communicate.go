package Bridge

import nw "BabelGo/Common/Network"

type GuiCom struct {
	ToNetwork chan *nw.Request
	ToGui     chan *nw.Request
}

func (c *GuiCom) Close() {
	close(c.ToNetwork)
	close(c.ToGui)
}

func (c *GuiCom) SendToNetwork(rq *nw.Request) {
	c.ToNetwork <- rq
}

func (c *GuiCom) SendToGui(rq *nw.Request) {
	c.ToGui <- rq
}

func (c *GuiCom) GetFromNetwork() *nw.Request {
	rq := <-c.ToGui
	return rq
}
func (c *GuiCom) GetFromGui() *nw.Request {
	rq := <-c.ToNetwork
	return rq
}
