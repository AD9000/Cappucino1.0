import React from 'react';
import { Board } from './Board';
import { Grid, Container, Paper } from '@material-ui/core';

export class App extends React.Component {
  render() {
    return (
      <Grid
        container
        spacing={0}
        direction="column"
        alignItems="center"
        justify="center"
        style={{ minHeight: '100vh' }}
      >
        <Grid item xs={3}>
          <Paper elevation={3}>
            <Board />
          </Paper>
        </Grid>
      </Grid>
    );
  }
}
