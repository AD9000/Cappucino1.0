import React from 'react';
import {
  Grid,
  Paper,
  Table,
  TableHead,
  TableRow,
  Tab,
  TableCell,
  createStyles,
  Checkbox,
  TableBody,
  makeStyles,
  Theme
} from '@material-ui/core';
import '../Board.css';
import '../chessFont.css';
import { withStyles } from '@material-ui/styles';
import { Square } from './Square';
import { Piece } from './Piece';
import { canMoveKnight, moveKnight } from './Game';
import { DndProvider } from 'react-dnd';
import Backend from 'react-dnd-html5-backend';
import BoardSquare from './BoardSquare';

const handleSquareClick = (toX: number, toY: number) => {
  if (canMoveKnight(toX, toY)) {
    moveKnight(toX, toY);
  }
};

const renderSquare = (i: number, [knightX, knightY]: number[]) => {
  const x = i % 8;
  const y = Math.floor(i / 8);
  const isKnightHere = x === knightX && y === knightY;
  const black = (x + y) % 2 === 1;
  const piece = isKnightHere ? <Piece /> : null;

  return (
    <div
      key={i}
      style={{ width: '12.5%', height: '12.5%' }}
      onClick={() => handleSquareClick(x, y)}
    >
      <BoardSquare x={x} y={y}>
        {isKnightHere && <Piece />}
      </BoardSquare>
      {/* <Square dark={black} children={piece} /> */}
    </div>
  );
};

const Board = ({ knightPosition }: { knightPosition: number[] }) => {
  // state = {
  //   board: [
  //     ['r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'],
  //     ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
  //     ['', '', '', '', '', '', '', ''],
  //     ['', '', '', '', '', '', '', ''],
  //     ['', '', '', '', '', '', '', ''],
  //     ['', '', '', '', '', '', '', ''],
  //     ['p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'],
  //     ['r', 'n', 'b', 'k', 'q', 'b', 'n', 'r']
  //   ]
  // };

  // render() {
  //   function createData(
  //     name: string,
  //     calories: number,
  //     fat: number,
  //     carbs: number,
  //     protein: number
  //   ) {
  //     return { name, calories, fat, carbs, protein };
  //   }

  //   const rows = [
  //     createData('Frozen yoghurt', 159, 6.0, 24, 4.0),
  //     createData('Ice cream sandwich', 237, 9.0, 37, 4.3),
  //     createData('Eclair', 262, 16.0, 24, 6.0),
  //     createData('Cupcake', 305, 3.7, 67, 4.3),
  //     createData('Gingerbread', 356, 16.0, 49, 3.9)
  //   ];

  //   const x = withStyles({
  //     piece: {
  //       fontFamily: 'Chess',
  //       textAlign: 'center'
  //     },
  //     lightbackground: {
  //       backgroundColor: 'burlywood',
  //       textAlign: 'center',
  //       fontFamily: 'Chess'
  //     }
  //   });

  //   const d = {
  //     lightbackground: {
  //       backgroundColor: 'burlywood',
  //       textAlign: 'center',
  //       fontFamily: 'Chess'
  //     }
  //   };

  const squares = [];
  for (let i = 0; i < 64; i++) {
    squares.push(renderSquare(i, knightPosition));
  }

  return (
    <DndProvider backend={Backend}>
      <div
        style={{
          width: '100%',
          height: '100%',
          display: 'flex',
          flexWrap: 'wrap'
        }}
      >
        {squares}
      </div>
    </DndProvider>
  );

  // const renderSquare = (
  //   child: JSX.Element | null,
  //   dark: boolean,
  //   index: number
  // ) => {
  //   return (
  //     <div key={index}>
  //       <Square dark={dark} child={null} />
  //     </div>
  //   );
  // };

  // const [x, y]: number[] = knightPosition;

  // return (
  //   <Paper>
  //     {Array(8)
  //       .map((_, i) => {
  //         return Array(8).map((_, j) => {
  //           const dark = (i + j) % 2 === 0;
  //           const index = i * 8 + j;
  //           if (i === x && j === 7 - y) {
  //             return renderSquare(<Piece />, dark, index);
  //           }
  //           return renderSquare(null, dark, index);
  //         });
  //       })
  //       .flat()}
  //   </Paper>
  // );
  // <Grid container className="Hi">
  //   <Grid container className="row">
  //     <Grid item xs={6}>
  //       <Paper className="data">Hi how are you</Paper>
  //     </Grid>
  //     <Grid item xs={6}>
  //       <Paper className="data">Hi how are you</Paper>
  //     </Grid>
  //   </Grid>
  //   <Grid item>
  //     <Paper className="data">Hi how are you</Paper>
  //   </Grid>
  // </Grid>
  // <Table>
  //   hi how are you
  // </Table>
  // <Table>
  //   <TableHead>
  //     <TableRow>
  //       {/* <TableCell style={d.lightbackground}>r</TableCell> */}
  //       <TableCell
  //         className="darkbackground"
  //         style={{ fontFamily: 'Chess', textAlign: 'center' }}
  //       >
  //         the quick brown fox jumped over the lazy dog
  //       </TableCell>
  //       <TableCell
  //         align="center"
  //         className="lightbackground"
  //         style={{ fontFamily: 'Chess' }}
  //       >
  //         r
  //       </TableCell>
  //       <TableCell
  //         className="lightbackground"
  //         style={{ fontFamily: 'Chess' }}
  //       >
  //         r
  //       </TableCell>
  //       <TableCell
  //         className="lightbackground"
  //         style={{ fontFamily: 'Chess' }}
  //       >
  //         r
  //       </TableCell>
  //       <TableCell
  //         className="lightbackground"
  //         style={{ fontFamily: 'Chess' }}
  //       >
  //         r
  //       </TableCell>
  //       <TableCell
  //         className="lightbackground"
  //         style={{ fontFamily: 'Chess' }}
  //       >
  //         r
  //       </TableCell>
  //       {/* <TableCell className={d.lightbackground}>r</TableCell> */}
  //     </TableRow>
  //   </TableHead>
  //   <TableBody>
  //     {/* {rows.map(row => (
  //         <TableRow key={row.name}>
  //           <TableCell component="th" scope="row">
  //             {row.name}
  //           </TableCell>
  //           <TableCell align="right">{row.calories}</TableCell>
  //           <TableCell align="right">{row.fat}</TableCell>
  //           <TableCell align="right">{row.carbs}</TableCell>
  //           <TableCell align="right">{row.protein}</TableCell>
  //         </TableRow>
  //       ))} */}
  //   </TableBody>
  // </Table>

  // <Table>
  //   <TableBody>
  //     {this.state.board.map((row, rIndex) => (
  //       <TableRow key={rIndex} style={{ height: '80px' }}>
  //         {row.map((cell, index) => (
  //           <TableCell
  //             key={index}
  //             className={
  //               (rIndex % 2 == 0 && index % 2 === 0) ||
  //               (index % 2 !== 0 && rIndex % 2 !== 0)
  //                 ? 'lightbackground'
  //                 : 'darkbackground'
  //             }
  //             style={{
  //               fontFamily: 'Chess',
  //               textAlign: 'center',
  //               width: '80px',
  //               fontSize: '2.5em'
  //             }}
  //           >
  //             {cell}
  //           </TableCell>
  //         ))}
  //       </TableRow>
  //     ))}
  //   </TableBody>
  // </Table>
};

export { Board };
