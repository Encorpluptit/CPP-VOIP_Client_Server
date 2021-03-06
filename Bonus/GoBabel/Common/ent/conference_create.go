// Code generated by entc, DO NOT EDIT.

package ent

import (
	"GoBabel/Common/ent/call"
	"GoBabel/Common/ent/conference"
	"GoBabel/Common/ent/user"
	"context"
	"fmt"

	"github.com/facebook/ent/dialect/sql/sqlgraph"
	"github.com/facebook/ent/schema/field"
)

// ConferenceCreate is the builder for creating a Conference entity.
type ConferenceCreate struct {
	config
	mutation *ConferenceMutation
	hooks    []Hook
}

// AddUserIDs adds the users edge to User by ids.
func (cc *ConferenceCreate) AddUserIDs(ids ...int) *ConferenceCreate {
	cc.mutation.AddUserIDs(ids...)
	return cc
}

// AddUsers adds the users edges to User.
func (cc *ConferenceCreate) AddUsers(u ...*User) *ConferenceCreate {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cc.AddUserIDs(ids...)
}

// AddCallIDs adds the calls edge to Call by ids.
func (cc *ConferenceCreate) AddCallIDs(ids ...int) *ConferenceCreate {
	cc.mutation.AddCallIDs(ids...)
	return cc
}

// AddCalls adds the calls edges to Call.
func (cc *ConferenceCreate) AddCalls(c ...*Call) *ConferenceCreate {
	ids := make([]int, len(c))
	for i := range c {
		ids[i] = c[i].ID
	}
	return cc.AddCallIDs(ids...)
}

// Mutation returns the ConferenceMutation object of the builder.
func (cc *ConferenceCreate) Mutation() *ConferenceMutation {
	return cc.mutation
}

// Save creates the Conference in the database.
func (cc *ConferenceCreate) Save(ctx context.Context) (*Conference, error) {
	if err := cc.preSave(); err != nil {
		return nil, err
	}
	var (
		err  error
		node *Conference
	)
	if len(cc.hooks) == 0 {
		node, err = cc.sqlSave(ctx)
	} else {
		var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
			mutation, ok := m.(*ConferenceMutation)
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
func (cc *ConferenceCreate) SaveX(ctx context.Context) *Conference {
	v, err := cc.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}

func (cc *ConferenceCreate) preSave() error {
	return nil
}

func (cc *ConferenceCreate) sqlSave(ctx context.Context) (*Conference, error) {
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

func (cc *ConferenceCreate) createSpec() (*Conference, *sqlgraph.CreateSpec) {
	var (
		c     = &Conference{config: cc.config}
		_spec = &sqlgraph.CreateSpec{
			Table: conference.Table,
			ID: &sqlgraph.FieldSpec{
				Type:   field.TypeInt,
				Column: conference.FieldID,
			},
		}
	)
	if nodes := cc.mutation.UsersIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: true,
			Table:   conference.UsersTable,
			Columns: conference.UsersPrimaryKey,
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
	if nodes := cc.mutation.CallsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.O2M,
			Inverse: false,
			Table:   conference.CallsTable,
			Columns: []string{conference.CallsColumn},
			Bidi:    false,
			Target: &sqlgraph.EdgeTarget{
				IDSpec: &sqlgraph.FieldSpec{
					Type:   field.TypeInt,
					Column: call.FieldID,
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

// ConferenceCreateBulk is the builder for creating a bulk of Conference entities.
type ConferenceCreateBulk struct {
	config
	builders []*ConferenceCreate
}

// Save creates the Conference entities in the database.
func (ccb *ConferenceCreateBulk) Save(ctx context.Context) ([]*Conference, error) {
	specs := make([]*sqlgraph.CreateSpec, len(ccb.builders))
	nodes := make([]*Conference, len(ccb.builders))
	mutators := make([]Mutator, len(ccb.builders))
	for i := range ccb.builders {
		func(i int, root context.Context) {
			builder := ccb.builders[i]
			var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
				if err := builder.preSave(); err != nil {
					return nil, err
				}
				mutation, ok := m.(*ConferenceMutation)
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
func (ccb *ConferenceCreateBulk) SaveX(ctx context.Context) []*Conference {
	v, err := ccb.Save(ctx)
	if err != nil {
		panic(err)
	}
	return v
}
