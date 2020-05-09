import React from 'react';
import { Board } from './components/Board';
import { Grid, Container, Paper } from '@material-ui/core';
import { Square } from './components/Square';
import { Piece } from './components/Piece';

export class App extends React.Component {
  render() {
    return (
      <Board knightPosition={[7, 4]} />
      // <Square dark={false} child={<Piece />} />
      // <Grid
      //   container
      //   spacing={0}
      //   direction="column"
      //   alignItems="center"
      //   justify="center"
      //   style={{ minHeight: '100vh', width: '100vw' }}
      // >
      //   <Grid item xs={3} style={{ maxWidth: '50%' }}>
      //     <Paper elevation={3} style={{ width: '100%' }}>
      //       <Board />
      //     </Paper>
      //   </Grid>
      // </Grid>
    );
  }
}
