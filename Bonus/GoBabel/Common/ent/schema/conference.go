package schema

import (
	"github.com/facebook/ent"
	"github.com/facebook/ent/schema/edge"
)

// Conference holds the schema definition for the Conference entity.
type Conference struct {
	ent.Schema
}

// Fields of the Conference.
func (Conference) Fields() []ent.Field {
	return nil
}

// Edges of the Conference.
func (Conference) Edges() []ent.Edge {
	return []ent.Edge{
		edge.From("users", User.Type).Ref("conferences"),
		edge.To("calls", Call.Type),
	}
}
