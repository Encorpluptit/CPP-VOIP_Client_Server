// Code generated by entc, DO NOT EDIT.

package ent

import (
	"GoBabel/Common/ent/call"
	"GoBabel/Common/ent/conference"
	"GoBabel/Common/ent/user"
	"context"
	"errors"
	"fmt"
	"time"

	"github.com/facebook/ent/dialect/sql/sqlgraph"
	"github.com/facebook/ent/schema/field"
)

// CallCreate is the builder for creating a Call entity.
type CallCreate struct {
	config
	mutation *CallMutation
	hooks    []Hook
}

// SetStartedAt sets the started_at field.
func (cc *CallCreate) SetStartedAt(t time.Time) *CallCreate {
	cc.mutation.SetStartedAt(t)
	return cc
}

// SetFinishedAt sets the finished_at field.
func (cc *CallCreate) SetFinishedAt(t time.Time) *CallCreate {
	cc.mutation.SetFinishedAt(t)
	return cc
}

// SetConferenceID sets the conference edge to Conference by id.
func (cc *CallCreate) SetConferenceID(id int) *CallCreate {
	cc.mutation.SetConferenceID(id)
	return cc
}

// SetNillableConferenceID sets the conference edge to Conference by id if the given value is not nil.
func (cc *CallCreate) SetNillableConferenceID(id *int) *CallCreate {
	if id != nil {
		cc = cc.SetConferenceID(*id)
	}
	return cc
}

// SetConference sets the conference edge to Conference.
func (cc *CallCreate) SetConference(c *Conference) *CallCreate {
	return cc.SetConferenceID(c.ID)
}

// AddParticipantIDs adds the participants edge to User by ids.
func (cc *CallCreate) AddParticipantIDs(ids ...int) *CallCreate {
	cc.mutation.AddParticipantIDs(ids...)
	return cc
}

// AddParticipants adds the participants edges to User.
func (cc *CallCreate) AddParticipants(u ...*User) *CallCreate {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cc.AddParticipantIDs(ids...)
}

// Mutation returns the CallMutation object of the builder.
func (cc *CallCreate) Mutation() *CallMutation {
	return cc.mutation
}

// Save creates the Call in the database.
func (cc *CallCreate) Save(ctx context.Context) (*Call, error) {
	if err := cc.preSave(); err != nil {
		return nil, err
	}
	var (
		err  error
		node *Call
	)
	if len(cc.hooks) == 0 {
		node, err = cc.sqlSave(ctx)
	} else {
		var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
			mutation, ok := m.(*CallMutation)
			if !ok {
				return nil, fmt.Errorf("unexpected mutation type %T", m)
			}
			cc.mutation = mutation
			node, err = cc.sqlSave(ctx)
			mutation.done = true
			return node, err
		})
		for i := len(cc.hooks) - 1; i >= 0; i-- {
			mut = cc.hooks[i](mut)
		}
		if _, err := mut.Mutate(ctx, cc.mutation); err != nil {
			return nil, err
		}
	}
	return node, err
}

// SaveX calls Save and panics if Save returns an error.
func (cc *CallCreate) SaveX(ctx context.Context) *Call {
	v, err := cc.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}

func (cc *CallCreate) preSave() error {
	if _, ok := cc.mutation.StartedAt(); !ok {
		return &ValidationError{Name: "started_at", err: errors.New("ent: missing required field \"started_at\"")}
	}
	if _, ok := cc.mutation.FinishedAt(); !ok {
		return &ValidationError{Name: "finished_at", err: errors.New("ent: missing required field \"finished_at\"")}
	}
	return nil
}

func (cc *CallCreate) sqlSave(ctx context.Context) (*Call, error) {
	c, _spec := cc.createSpec()
	if err := sqlgraph.CreateNode(ctx, cc.driver, _spec); err != nil {
		if cerr, ok := isSQLConstraintError(err); ok {
			err = cerr
		}
		return nil, err
	}
	id := _spec.ID.Value.(int64)
	c.ID = int(id)
	return c, nil
}

func (cc *CallCreate) createSpec() (*Call, *sqlgraph.CreateSpec) {
	var (
		c     = &Call{config: cc.config}
		_spec = &sqlgraph.CreateSpec{
			Table: call.Table,
			ID: &sqlgraph.FieldSpec{
				Type:   field.TypeInt,
				Column: call.FieldID,
			},
		}
	)
	if value, ok := cc.mutation.StartedAt(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeTime,
			Value:  value,
			Column: call.FieldStartedAt,
		})
		c.StartedAt = value
	}
	if value, ok := cc.mutation.FinishedAt(); ok {
		_spec.Fields = append(_spec.Fields, &sqlgraph.FieldSpec{
			Type:   field.TypeTime,
			Value:  value,
			Column: call.FieldFinishedAt,
		})
		c.FinishedAt = value
	}
	if nodes := cc.mutation.ConferenceIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2O,
			Inverse: true,
			Table:   call.ConferenceTable,
			Columns: []string{call.ConferenceColumn},
			Bidi:    false,
			Target: &sqlgraph.EdgeTarget{
				IDSpec: &sqlgraph.FieldSpec{
					Type:   field.TypeInt,
					Column: conference.FieldID,
				},
			},
		}
		for _, k := range nodes {
			edge.Target.Nodes = append(edge.Target.Nodes, k)
		}
		_spec.Edges = append(_spec.Edges, edge)
	}
	if nodes := cc.mutation.ParticipantsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: true,
			Table:   call.ParticipantsTable,
			Columns: call.ParticipantsPrimaryKey,
			Bidi:    false,
			Target: &sqlgraph.EdgeTarget{
				IDSpec: &sqlgraph.FieldSpec{
					Type:   field.TypeInt,
					Column: user.FieldID,
				},
			},
		}
		for _, k := range nodes {
			edge.Target.Nodes = append(edge.Target.Nodes, k)
		}
		_spec.Edges = append(_spec.Edges, edge)
	}
	return c, _spec
}

// CallCreateBulk is the builder for creating a bulk of Call entities.
type CallCreateBulk struct {
	config
	builders []*CallCreate
}

// Save creates the Call entities in the database.
func (ccb *CallCreateBulk) Save(ctx context.Context) ([]*Call, error) {
	specs := make([]*sqlgraph.CreateSpec, len(ccb.builders))
	nodes := make([]*Call, len(ccb.builders))
	mutators := make([]Mutator, len(ccb.builders))
	for i := range ccb.builders {
		func(i int, root context.Context) {
			builder := ccb.builders[i]
			var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
				if err := builder.preSave(); err != nil {
					return nil, err
				}
				mutation, ok := m.(*CallMutation)
				if !ok {
					return nil, fmt.Errorf("unexpected mutation type %T", m)
				}
				builder.mutation = mutation
				nodes[i], specs[i] = builder.createSpec()
				var err error
				if i < len(mutators)-1 {
					_, err = mutators[i+1].Mutate(root, ccb.builders[i+1].mutation)
				} else {
					// Invoke the actual operation on the latest mutation in the chain.
					if err = sqlgraph.BatchCreate(ctx, ccb.driver, &sqlgraph.BatchCreateSpec{Nodes: specs}); err != nil {
						if cerr, ok := isSQLConstraintError(err); ok {
							err = cerr
						}
					}
				}
				mutation.done = true
				if err != nil {
					return nil, err
				}
				id := specs[i].ID.Value.(int64)
				nodes[i].ID = int(id)
				return nodes[i], nil
			})
			for i := len(builder.hooks) - 1; i >= 0; i-- {
				mut = builder.hooks[i](mut)
			}
			mutators[i] = mut
		}(i, ctx)
	}
	if len(mutators) > 0 {
		if _, err := mutators[0].Mutate(ctx, ccb.builders[0].mutation); err != nil {
			return nil, err
		}
	}
	return nodes, nil
}

// SaveX calls Save and panics if Save returns an error.
func (ccb *CallCreateBulk) SaveX(ctx context.Context) []*Call {
	v, err := ccb.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}
