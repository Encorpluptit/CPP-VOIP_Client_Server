package schema

import (
	"github.com/facebook/ent"
	"github.com/facebook/ent/schema/edge"
)

// Conferences holds the schema definition for the Conferences entity.
type Conferences struct {
	ent.Schema
}

// Fields of the Conferences.
func (Conferences) Fields() []ent.Field {
	return nil
}

// Edges of the Conferences.
func (Conferences) Edges() []ent.Edge {
	return []ent.Edge{
		edge.To("users", User.Type),
	}
}
