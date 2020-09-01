package schema

import (
	"github.com/facebook/ent"
	"github.com/facebook/ent/schema/edge"
	"github.com/facebook/ent/schema/field"
)

// Call holds the schema definition for the Call entity.
type Call struct {
	ent.Schema
}

// Fields of the Call.
func (Call) Fields() []ent.Field {
	return []ent.Field{
		field.Time("started_at"),
		field.Time("finished_at"),
	}
}

// Edges of the Call.
func (Call) Edges() []ent.Edge {
	return []ent.Edge{
		edge.From("conference", Conference.Type).Ref("calls").Unique(),
		edge.From("participants", User.Type).Ref("calls"),
	}
}
