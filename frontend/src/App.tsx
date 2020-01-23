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
        style={{ minHeight: '100vh', width: '100vw' }}
      >
        <Grid item xs={3} style={{ maxWidth: '50%' }}>
          <Paper elevation={3} style={{ width: '100%' }}>
            <Board />
          </Paper>
        </Grid>
      </Grid>
    );
  }
}
