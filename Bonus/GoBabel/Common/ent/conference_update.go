// Code generated by entc, DO NOT EDIT.

package ent

import (
	"GoBabel/Common/ent/call"
	"GoBabel/Common/ent/conference"
	"GoBabel/Common/ent/predicate"
	"GoBabel/Common/ent/user"
	"context"
	"fmt"

	"github.com/facebook/ent/dialect/sql"
	"github.com/facebook/ent/dialect/sql/sqlgraph"
	"github.com/facebook/ent/schema/field"
)

// ConferenceUpdate is the builder for updating Conference entities.
type ConferenceUpdate struct {
	config
	hooks      []Hook
	mutation   *ConferenceMutation
	predicates []predicate.Conference
}

// Where adds a new predicate for the builder.
func (cu *ConferenceUpdate) Where(ps ...predicate.Conference) *ConferenceUpdate {
	cu.predicates = append(cu.predicates, ps...)
	return cu
}

// AddUserIDs adds the users edge to User by ids.
func (cu *ConferenceUpdate) AddUserIDs(ids ...int) *ConferenceUpdate {
	cu.mutation.AddUserIDs(ids...)
	return cu
}

// AddUsers adds the users edges to User.
func (cu *ConferenceUpdate) AddUsers(u ...*User) *ConferenceUpdate {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cu.AddUserIDs(ids...)
}

// AddCallIDs adds the calls edge to Call by ids.
func (cu *ConferenceUpdate) AddCallIDs(ids ...int) *ConferenceUpdate {
	cu.mutation.AddCallIDs(ids...)
	return cu
}

// AddCalls adds the calls edges to Call.
func (cu *ConferenceUpdate) AddCalls(c ...*Call) *ConferenceUpdate {
	ids := make([]int, len(c))
	for i := range c {
		ids[i] = c[i].ID
	}
	return cu.AddCallIDs(ids...)
}

// Mutation returns the ConferenceMutation object of the builder.
func (cu *ConferenceUpdate) Mutation() *ConferenceMutation {
	return cu.mutation
}

// RemoveUserIDs removes the users edge to User by ids.
func (cu *ConferenceUpdate) RemoveUserIDs(ids ...int) *ConferenceUpdate {
	cu.mutation.RemoveUserIDs(ids...)
	return cu
}

// RemoveUsers removes users edges to User.
func (cu *ConferenceUpdate) RemoveUsers(u ...*User) *ConferenceUpdate {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cu.RemoveUserIDs(ids...)
}

// RemoveCallIDs removes the calls edge to Call by ids.
func (cu *ConferenceUpdate) RemoveCallIDs(ids ...int) *ConferenceUpdate {
	cu.mutation.RemoveCallIDs(ids...)
	return cu
}

// RemoveCalls removes calls edges to Call.
func (cu *ConferenceUpdate) RemoveCalls(c ...*Call) *ConferenceUpdate {
	ids := make([]int, len(c))
	for i := range c {
		ids[i] = c[i].ID
	}
	return cu.RemoveCallIDs(ids...)
}

// Save executes the query and returns the number of rows/vertices matched by this operation.
func (cu *ConferenceUpdate) Save(ctx context.Context) (int, error) {

	var (
		err      error
		affected int
	)
	if len(cu.hooks) == 0 {
		affected, err = cu.sqlSave(ctx)
	} else {
		var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
			mutation, ok := m.(*ConferenceMutation)
			if !ok {
				return nil, fmt.Errorf("unexpected mutation type %T", m)
			}
			cu.mutation = mutation
			affected, err = cu.sqlSave(ctx)
			mutation.done = true
			return affected, err
		})
		for i := len(cu.hooks) - 1; i >= 0; i-- {
			mut = cu.hooks[i](mut)
		}
		if _, err := mut.Mutate(ctx, cu.mutation); err != nil {
			return 0, err
		}
	}
	return affected, err
}

// SaveX is like Save, but panics if an error occurs.
func (cu *ConferenceUpdate) SaveX(ctx context.Context) int {
	affected, err := cu.Save(ctx)
	if err != nil {
		panic(err)
	}
	return affected
}

// Exec executes the query.
func (cu *ConferenceUpdate) Exec(ctx context.Context) error {
	_, err := cu.Save(ctx)
	return err
}

// ExecX is like Exec, but panics if an error occurs.
func (cu *ConferenceUpdate) ExecX(ctx context.Context) {
	if err := cu.Exec(ctx); err != nil {
		panic(err)
	}
}

func (cu *ConferenceUpdate) sqlSave(ctx context.Context) (n int, err error) {
	_spec := &sqlgraph.UpdateSpec{
		Node: &sqlgraph.NodeSpec{
			Table:   conference.Table,
			Columns: conference.Columns,
			ID: &sqlgraph.FieldSpec{
				Type:   field.TypeInt,
				Column: conference.FieldID,
			},
		},
	}
	if ps := cu.predicates; len(ps) > 0 {
		_spec.Predicate = func(selector *sql.Selector) {
			for i := range ps {
				ps[i](selector)
			}
		}
	}
	if nodes := cu.mutation.RemovedUsersIDs(); len(nodes) > 0 {
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
		_spec.Edges.Clear = append(_spec.Edges.Clear, edge)
	}
	if nodes := cu.mutation.UsersIDs(); len(nodes) > 0 {
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
		_spec.Edges.Add = append(_spec.Edges.Add, edge)
	}
	if nodes := cu.mutation.RemovedCallsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: false,
			Table:   conference.CallsTable,
			Columns: conference.CallsPrimaryKey,
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
		_spec.Edges.Clear = append(_spec.Edges.Clear, edge)
	}
	if nodes := cu.mutation.CallsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: false,
			Table:   conference.CallsTable,
			Columns: conference.CallsPrimaryKey,
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
		_spec.Edges.Add = append(_spec.Edges.Add, edge)
	}
	if n, err = sqlgraph.UpdateNodes(ctx, cu.driver, _spec); err != nil {
		if _, ok := err.(*sqlgraph.NotFoundError); ok {
			err = &NotFoundError{conference.Label}
		} else if cerr, ok := isSQLConstraintError(err); ok {
			err = cerr
		}
		return 0, err
	}
	return n, nil
}

// ConferenceUpdateOne is the builder for updating a single Conference entity.
type ConferenceUpdateOne struct {
	config
	hooks    []Hook
	mutation *ConferenceMutation
}

// AddUserIDs adds the users edge to User by ids.
func (cuo *ConferenceUpdateOne) AddUserIDs(ids ...int) *ConferenceUpdateOne {
	cuo.mutation.AddUserIDs(ids...)
	return cuo
}

// AddUsers adds the users edges to User.
func (cuo *ConferenceUpdateOne) AddUsers(u ...*User) *ConferenceUpdateOne {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cuo.AddUserIDs(ids...)
}

// AddCallIDs adds the calls edge to Call by ids.
func (cuo *ConferenceUpdateOne) AddCallIDs(ids ...int) *ConferenceUpdateOne {
	cuo.mutation.AddCallIDs(ids...)
	return cuo
}

// AddCalls adds the calls edges to Call.
func (cuo *ConferenceUpdateOne) AddCalls(c ...*Call) *ConferenceUpdateOne {
	ids := make([]int, len(c))
	for i := range c {
		ids[i] = c[i].ID
	}
	return cuo.AddCallIDs(ids...)
}

// Mutation returns the ConferenceMutation object of the builder.
func (cuo *ConferenceUpdateOne) Mutation() *ConferenceMutation {
	return cuo.mutation
}

// RemoveUserIDs removes the users edge to User by ids.
func (cuo *ConferenceUpdateOne) RemoveUserIDs(ids ...int) *ConferenceUpdateOne {
	cuo.mutation.RemoveUserIDs(ids...)
	return cuo
}

// RemoveUsers removes users edges to User.
func (cuo *ConferenceUpdateOne) RemoveUsers(u ...*User) *ConferenceUpdateOne {
	ids := make([]int, len(u))
	for i := range u {
		ids[i] = u[i].ID
	}
	return cuo.RemoveUserIDs(ids...)
}

// RemoveCallIDs removes the calls edge to Call by ids.
func (cuo *ConferenceUpdateOne) RemoveCallIDs(ids ...int) *ConferenceUpdateOne {
	cuo.mutation.RemoveCallIDs(ids...)
	return cuo
}

// RemoveCalls removes calls edges to Call.
func (cuo *ConferenceUpdateOne) RemoveCalls(c ...*Call) *ConferenceUpdateOne {
	ids := make([]int, len(c))
	for i := range c {
		ids[i] = c[i].ID
	}
	return cuo.RemoveCallIDs(ids...)
}

// Save executes the query and returns the updated entity.
func (cuo *ConferenceUpdateOne) Save(ctx context.Context) (*Conference, error) {

	var (
		err  error
		node *Conference
	)
	if len(cuo.hooks) == 0 {
		node, err = cuo.sqlSave(ctx)
	} else {
		var mut Mutator = MutateFunc(func(ctx context.Context, m Mutation) (Value, error) {
			mutation, ok := m.(*ConferenceMutation)
			if !ok {
				return nil, fmt.Errorf("unexpected mutation type %T", m)
			}
			cuo.mutation = mutation
			node, err = cuo.sqlSave(ctx)
			mutation.done = true
			return node, err
		})
		for i := len(cuo.hooks) - 1; i >= 0; i-- {
			mut = cuo.hooks[i](mut)
		}
		if _, err := mut.Mutate(ctx, cuo.mutation); err != nil {
			return nil, err
		}
	}
	return node, err
}

// SaveX is like Save, but panics if an error occurs.
func (cuo *ConferenceUpdateOne) SaveX(ctx context.Context) *Conference {
	c, err := cuo.Save(ctx)
	if err != nil {
		panic(err)
	}
	return c
}

// Exec executes the query on the entity.
func (cuo *ConferenceUpdateOne) Exec(ctx context.Context) error {
	_, err := cuo.Save(ctx)
	return err
}

// ExecX is like Exec, but panics if an error occurs.
func (cuo *ConferenceUpdateOne) ExecX(ctx context.Context) {
	if err := cuo.Exec(ctx); err != nil {
		panic(err)
	}
}

func (cuo *ConferenceUpdateOne) sqlSave(ctx context.Context) (c *Conference, err error) {
	_spec := &sqlgraph.UpdateSpec{
		Node: &sqlgraph.NodeSpec{
			Table:   conference.Table,
			Columns: conference.Columns,
			ID: &sqlgraph.FieldSpec{
				Type:   field.TypeInt,
				Column: conference.FieldID,
			},
		},
	}
	id, ok := cuo.mutation.ID()
	if !ok {
		return nil, &ValidationError{Name: "ID", err: fmt.Errorf("missing Conference.ID for update")}
	}
	_spec.Node.ID.Value = id
	if nodes := cuo.mutation.RemovedUsersIDs(); len(nodes) > 0 {
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
		_spec.Edges.Clear = append(_spec.Edges.Clear, edge)
	}
	if nodes := cuo.mutation.UsersIDs(); len(nodes) > 0 {
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
		_spec.Edges.Add = append(_spec.Edges.Add, edge)
	}
	if nodes := cuo.mutation.RemovedCallsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: false,
			Table:   conference.CallsTable,
			Columns: conference.CallsPrimaryKey,
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
		_spec.Edges.Clear = append(_spec.Edges.Clear, edge)
	}
	if nodes := cuo.mutation.CallsIDs(); len(nodes) > 0 {
		edge := &sqlgraph.EdgeSpec{
			Rel:     sqlgraph.M2M,
			Inverse: false,
			Table:   conference.CallsTable,
			Columns: conference.CallsPrimaryKey,
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
		_spec.Edges.Add = append(_spec.Edges.Add, edge)
	}
	c = &Conference{config: cuo.config}
	_spec.Assign = c.assignValues
	_spec.ScanValues = c.scanValues()
	if err = sqlgraph.UpdateNode(ctx, cuo.driver, _spec); err != nil {
		if _, ok := err.(*sqlgraph.NotFoundError); ok {
			err = &NotFoundError{conference.Label}
		} else if cerr, ok := isSQLConstraintError(err); ok {
			err = cerr
		}
		return nil, err
	}
	return c, nil
}
